/******************************************************************************
 *
 * Module: Motor
 *
 * File Name: motor.h
 *
 * Description: Source file for the motor driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/
#include "motor.h"
#include "pwm.h"/* to use pwm to control speed */
//#include "common_macros.h" /* To use the macros like SET_BIT */

void DcMotor_Init(void) {
	/* configure pin PB0 and PB1 as output pins */
	GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_INPUT0_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_INPUT1_ID, PIN_OUTPUT);
	/* configure Enable pin PB3 as output pin */
	GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_ENABLE_ID, PIN_OUTPUT);
	/* Disabling the  Enable pin PB3  pin */
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_ENABLE_ID, LOGIC_LOW);
	/*Stopping the DC Motor at first by writing zero's on the INPUTS */
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_INPUT0_ID, LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_INPUT1_ID, LOGIC_LOW);

}
void DcMotor_Rotate(DcMotor_State state, uint8 speed) {
	/* making sure the speed that has been entering is between 0 & 100 else do nothing*/
	if ((speed>=0) && (speed<=100)){
		switch (state) {
		case STOPPED: {
			/*Stopping the DC Motor at first by writing zero's on the INPUTS */
			GPIO_writePin(MOTOR_PORT_ID, MOTOR_INPUT0_ID, LOGIC_LOW);
			GPIO_writePin(MOTOR_PORT_ID, MOTOR_INPUT1_ID, LOGIC_LOW);
			/*Sending the speed of the motor between 0-->100 */
			Timer0_PWM_Start(speed);
			break;
		}
		case CLOCKWISE: {
			/*Enabling  the DC Motor Anticlockwise by writing zero on the INPUT1 and one in INPUT0 */
			GPIO_writePin(MOTOR_PORT_ID, MOTOR_INPUT0_ID, LOGIC_HIGH);
			GPIO_writePin(MOTOR_PORT_ID, MOTOR_INPUT1_ID, LOGIC_LOW);
			/*Sending the speed of the motor between 0-->100 */
			Timer0_PWM_Start(speed);

			break;
		}
		case ANTICLOCKWISE: {
			/*Enabling  the DC Motor Anticlockwise by writing zero on the INPUT0 and one in INPUT1 */
			GPIO_writePin(MOTOR_PORT_ID, MOTOR_INPUT0_ID, LOGIC_LOW);
			GPIO_writePin(MOTOR_PORT_ID, MOTOR_INPUT1_ID, LOGIC_HIGH);
			/*Sending the speed of the motor between 0-->100 */
			Timer0_PWM_Start(speed);
			break;
		}
		}
	}
	else{}


}

