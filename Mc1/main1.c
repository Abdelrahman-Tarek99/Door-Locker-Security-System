#include "keypad.h"
#include "lcd.h"
#include "timer1.h"
#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define PASSED 1
#define FAILED 0
void Menu1(void);
void Menu2(void);
uint8 counter = 0;
uint8 Condition, Plus_Minus, cnt = 0;
uint8 Password[7], Password_Confirmation[7], i = 0,z=0, Password_check,
		Password_For_Door_Unlocking[7], Password_Changed[7];
Timer1_ConfigType Timer1_ConfigTypee = { 0, 3907, CPU_1024, CTC }; //23437
UART_ConfigType UART_ConfigTypee = { BIT8, DISABLED, BIT1, 9600 };

//...................................................................
void Menu1(void) {
	LCD_clearScreen();

	LCD_displayString("plz enter pass:");
	LCD_moveCursor(1, 0);
	//Timer1_ConfigTypee.compare_value=3907;
	while (1) {
		Password_check = KEYPAD_getPressedKey();
		if ((cnt < 5) && (Password_check >= 0) && (Password_check <= 9)) {
			Password[i] = Password_check;
			LCD_displayCharacter('*');
			Timer1_init(&Timer1_ConfigTypee);
			while (counter < 1)
				;
			counter = 0;
			Timer1_deInit();
			i++;
			cnt++;
		}

		if (Password_check == 13) {
			Password[i] = '#';
			Password[i + 1] = '\0';
			UART_sendString(Password); //Recieving it in Variable "Recieved_Password(MC2)"
			Timer1_init(&Timer1_ConfigTypee);
			while (counter < 1)
				;
			counter = 0;
			Timer1_deInit();
			LCD_clearScreen();
			Password_check = 0;
			i = 0;
			cnt = 0;
			break;
		}

	}

	LCD_displayString("plz re-enter the");
	LCD_moveCursor(1, 0);
	LCD_displayString("same pass:");
	while (1) {
		Password_check = KEYPAD_getPressedKey();
		if ((cnt < 5) && (Password_check >= 0) && (Password_check <= 9)) {
			Password[i] = Password_check;
			LCD_displayCharacter('*');
			Timer1_init(&Timer1_ConfigTypee);
			while (counter < 1)
				;
			counter = 0;
			Timer1_deInit();
			i++;
		}

		if (Password_check == 13) {
			Password[i] = '#';
			Password[i + 1] = '\0';
			UART_sendString(Password); //Recieving it in Variable "Recieved_Second_Password(MC2)"
			Timer1_init(&Timer1_ConfigTypee);
			while (counter < 1)
				;
			counter = 0;
			Timer1_deInit();
			LCD_clearScreen();
			Password_check = 0;
			i = 0;
			cnt = 0;
			break;
		}

	}

	Condition = UART_recieveByte(); //recieving a byte form MC2 saying that the first 2 passwords matched or not

	if (Condition == PASSED) {
		Menu2();
	}

}

//...................................................................
void Menu2(void) {
	uint8 check_Password_changed_Condition;

	LCD_displayString("+:Open Door");
	LCD_moveCursor(1, 0);
	LCD_displayString("-:Change pass");
	Plus_Minus = KEYPAD_getPressedKey();
	UART_sendByte(Plus_Minus);
	LCD_clearScreen();

	if (Plus_Minus == '+') {
		LCD_displayString("plz enter pass:");
		LCD_moveCursor(1, 0);
		while (1) {
			Password_check = KEYPAD_getPressedKey();
			if ((cnt < 5) && (Password_check >= 0) && (Password_check <= 9)) {
				Password_For_Door_Unlocking[i] = Password_check;
				LCD_displayCharacter('*');
				Timer1_init(&Timer1_ConfigTypee);
				while (counter < 1)
					counter = 0;
				Timer1_deInit();
				i++;
			}
			if (Password_check == 13) {
				Password_For_Door_Unlocking[i] = '#';
				Password_For_Door_Unlocking[i + 1] = '\0';
				UART_sendString(Password_For_Door_Unlocking);
				Timer1_init(&Timer1_ConfigTypee);
				while (counter < 1)
					;
				counter = 0;
				Timer1_deInit();
				LCD_clearScreen();
				Password_check = 0;
				i = 0;
				cnt = 0;
				break;
			}
		}
		Condition = UART_recieveByte();
		if (Condition == PASSED) {
			LCD_clearScreen();
			LCD_displayString("Door is Unlocking");
			Timer1_init(&Timer1_ConfigTypee);
			while (counter < 6)
				; //hold screen for 18 sec LCD:15sec & Motor 3sec.
			counter = 0;
			Timer1_deInit();
			LCD_clearScreen();
			LCD_displayString("Door is locking");
			Timer1_init(&Timer1_ConfigTypee);
			while (counter < 5)
				; //hold screen while door is locking while the motor i rotating ACW
			counter = 0;
			Timer1_deInit();

		}
	}

	else {

		LCD_displayString("plz enter pass:");
		LCD_moveCursor(1, 0);
		while (1) {
			for (z = 0; z < 3; z++){
				Password_check = KEYPAD_getPressedKey();
				if ((cnt < 5) && (Password_check >= 0) && (Password_check <= 9)) {
					Password_Changed[i] = Password_check;
					LCD_displayCharacter('*');
					Timer1_init(&Timer1_ConfigTypee);
					while (counter < 1)
						;
					counter = 0;
					Timer1_deInit();
					i++;
				}
				if (Password_check == 13) {
					Password_Changed[i] = '#';
					Password_Changed[i + 1] = '\0';
					UART_sendString(Password_Changed); //sending it to MC2 in Variable Called"New_Pasword"
					Timer1_init(&Timer1_ConfigTypee);
					while (counter < 1)
						;
					counter = 0;
					Timer1_deInit();
					LCD_clearScreen();
					Password_check = 0;
					i = 0;
					break;
				}
			}//end of for loop of Max 3 times

		}

		check_Password_changed_Condition = UART_recieveByte(); //checked by Flag2 in MC2
		if (check_Password_changed_Condition == PASSED) {
			Menu1();
		}
//the else will automatic Return to Menu 2
	}
}

//................................................................
void Into1(void) {
	counter++;
}

int main(void) {
	UART_init(&UART_ConfigTypee);
	Timer1_setCallBack(Into1);
	LCD_init();
	SREG |= (1 << 7);
	Menu1();

}

