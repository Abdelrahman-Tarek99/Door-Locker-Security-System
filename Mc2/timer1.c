#include "timer1.h"
#include <avr/io.h>
#include<avr/interrupt.h>

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

ISR(TIMER1_COMPA_vect) {
	if (g_callBackPtr != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER1_OVF_vect) {
	if (g_callBackPtr != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

void Timer1_init(const Timer1_ConfigType *Config_Ptr) {
	TCNT1 = Config_Ptr->initial_value; //timer initial value
	OCR1A = Config_Ptr->compare_value; //compare value
	TIMSK |= (1 << OCIE1A); //enable compare interrupt for channel A
	/* Configure timer1 control registers
	 * 1. Non PWM mode FOC1A=1 and FOC1B=1
	 * 2. No need for OC1A & OC1B in this example so COM1A0=0 & COM1A1=0 & COM1B0=0 & COM1B1=0
	 * 3. CTC Mode and compare value in OCR1A WGM10=0 & WGM11=0 & WGM12=1 & WGM13=0
	 */
	TCCR1A = (1 << FOC1A) | (1 << FOC1B);
	/*
	 * 4. Clock = F_CPU/1024 CS10=1 CS11=0 CS12=1
	 */
	TCCR1B = Config_Ptr->mode | Config_Ptr->prescaler;

}
void Timer1_deInit(void) {
	TCNT1 = 0;
	OCR1A = 0;
	TIMSK = 0;
	TCCR1A = 0;
	TCCR1B = 0;
}
void Timer1_setCallBack(void (*a_ptr)(void)) {
	g_callBackPtr = a_ptr;
}

