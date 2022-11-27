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
#ifndef BUZZER_H_
#define BUZZER_H_
#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define BUZZER_PORT_ID PORTA_ID
#define BUZZER_PIN_ID PIN0_ID

void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);



#endif /* BUZZER_H_ */
