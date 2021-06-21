/*  module name :timer driver
 *
 *  file name :timer.h
 *
 *  description :the header file of timer driver
 *
 *
 *   Author: Hesham Salem
 */

#ifndef TIMER_H_
#define TIMER_H_
#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"
#include <string.h>

/***************************************************************
 * 		structure used in timer configuration 						*
 * *************************************************************
 */
typedef struct
{
	uint8 timerNumber;
	char mode[20];/* string copy --->> ( "compare" ,"normal" or "PWM") */
	uint16 prescaler; /* (1,64,256 or 1024) */
	char compareMatchMode[20]; /* string copy --->> ( "toggle" ,"clear" or "set")  or the default will be oc disconnected */
	char pwmMode[20];/* string copy --->> ( "inverting"  or "non-inverting") */

}TIMER_configurationType;

/***************************************************************
 * 					functions prototyping 						*
 * *************************************************************
 */

void TIMER_init( TIMER_configurationType * config);
void TIMER_setCompare(uint16 compareValue);
void TIMER_setNormal(uint8 initValue);
void TIMER_setCallBackPtr(void(*a_ptr)(void));
void TIMER_setpwm(uint8 dutyCycle);
void TIMER_stop();


#endif /* TIMER_H_ */
