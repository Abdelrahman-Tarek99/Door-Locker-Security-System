 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: Header file for the pwm driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/
#ifndef PWM_H_
#define PWM_H_
#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PWM_FREQUENCY 500;
#define COMPARE_VALUE_PORT_ID PORTB_ID
#define COMPARE_VALUE_PIN_ID PIN3_ID
typedef enum
{
	NOCLOCK,NOPRESCALER,FCPU_8,FCPU_64,FCPU_256,FCPU_1024,FCPU_EXTERNALCLOCK_FALLINGEDGE,FCPU_EXTERNALCLOCK_RISINGEDGE
}Pwm_Prescaler;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void Timer0_PWM_Start(unsigned char set_duty_cycle);

#endif /* PWM_H_ */
