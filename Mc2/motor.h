/******************************************************************************
 *
 * Module: Motor
 *
 * File Name: motor.h
 *
 * Description: Header file for the motor driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#ifndef MOTOR_H_
#define MOTOR_H_
#include "std_types.h"
#include "gpio.h"
#include "avr\io.h" /* To use motor Registers */
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* Motor HW Ports and Pins Ids */
#define MOTOR_INPUT0_ID PIN2_ID
#define MOTOR_INPUT1_ID PIN1_ID
#define MOTOR_ENABLE_ID PIN3_ID
#define MOTOR_PORT_ID PORTB_ID
typedef enum {
	STOPPED, CLOCKWISE, ANTICLOCKWISE
} DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize the motor:
 * 1. Setup the motor pins directions by use the GPIO driver.
 */
void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif /* MOTOR_H_ */
