 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for the Keypad driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

typedef enum
{
	NOCLOCK,NOPRESCALER,CPU_8,CPU_64,CPU_256,CPU_1024,CPU_EXTERNALCLOCK_FALLINGEDGE,CPU_EXTERNALCLOCK_RISINGEDGE
}Timer1_Prescaler;

typedef enum{
	NORMAL,CTC=8
}Timer1_Mode;


typedef struct {
uint16 initial_value;
uint16 compare_value; // it will be used in compare mode only.
Timer1_Prescaler prescaler;
Timer1_Mode mode;
} Timer1_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void Timer1_init(const Timer1_ConfigType * Config_Ptr);
void Timer1_deInit(void);
void Timer1_setCallBack(void(*a_ptr)(void));




#endif /* TIMER1_H_ */
