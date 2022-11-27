#include "timer1.h"
#include "motor.h"
#include "twi.h"
#include "uart.h"
#include "buzzer.h"
#include "external_eeprom.h"
#define PASSED 1
#define FAILED 0
uint8 i = 0, Flag = 1, Flag2 = 1, count = 0, Option_Choosed, Timer_Counter = 0;
uint8 Recieved_Password[7], Recieved_Second_Password[7], New_Pasword[7],
		Password_For_Door_Unlocking[7];
Timer1_ConfigType Timer1_ConfigTypee = { 0, 3907, CPU_1024, CTC }; //23437
UART_ConfigType UART_ConfigTypee = { BIT8, DISABLED, BIT1, 9600 };
TWI_ConfigType TWI_ConfigTypee = { 2, 2 };
//.....................................................
void Into2(void) {
	count++;
}
//.....................................................
int main(void) {
	UART_init(&UART_ConfigTypee);
	DcMotor_Init();
	Buzzer_init();
	TWI_init(&TWI_ConfigTypee);
	Timer1_setCallBack(Into2);
	while (1) {
		UART_receiveString(Recieved_Password);

		UART_receiveString(Recieved_Second_Password);

		while (Recieved_Password[i] != '\0') {
			if (Recieved_Password[i] == Recieved_Second_Password[i]) {
				i++;
			} else {
				Flag = 0;
				break;
			}
		}
		if (Flag == 1) {

			UART_sendByte(1); //Sending that the first two paswords matched correctly
			Option_Choosed = UART_recieveByte(); //recieving the "+" or "-" user chosed
			if (Option_Choosed == '+') {

				for (i = 0; i < 3; i++) {
					UART_receiveString(Password_For_Door_Unlocking);
					while (Recieved_Password[i] != '\0') {
						if (Recieved_Password[i]
								== Password_For_Door_Unlocking[i]) {
							i++;
						} else {
							Flag = 0;
							UART_sendByte(FAILED);
							break; //ha5rog mn el for loop
						}

					}
				}
				if (Flag == 1) {
					DcMotor_Rotate(CLOCKWISE, 100);
					Timer1_init(&Timer1_ConfigTypee);
					while (Timer_Counter < 5)
						;
					Timer_Counter = 0;
					Timer1_deInit();
				} else {
					Flag = 1;
					Buzzer_on();
					DcMotor_Rotate(STOPPED,0);
					Timer1_init(&Timer1_ConfigTypee);
					while (Timer_Counter == 20)
						;

					Timer_Counter = 0;
					Timer1_deInit();

				}

			} else {
				while (1) {
					//Recieving the new password after changing it
					for (i = 0; i < 3; i++) {
						UART_receiveString(New_Pasword); //Recieving it from MC1 from Variable Called "Password_Changed"
						while (Recieved_Password[i] != '\0') {
							if (Recieved_Password[i] == New_Pasword[i]) {
								Flag2 = 1;
								i++;
								break;
							} else {
								Flag2 = 0;
							}
						}

					}
					if (Flag2 == 1) {
						UART_sendByte(PASSED);
					} else {
						Buzzer_on();
						Timer1_init(&Timer1_ConfigTypee);
						while (Timer_Counter == 20)
							;

						Timer_Counter = 0;
						Timer1_deInit();
						UART_sendByte(FAILED);
					}
				}
			}

		} else {
			UART_sendByte(FAILED);
		}
		i = 0;
		Flag = 1;

	}
}
