/*
 * timer.h
 *
 *  Created on: Jun 11, 2021
 *      Author: hesham
 */

#ifndef TIMER_H_
#define TIMER_H_
#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"
#include <string.h>
typedef struct
{
	uint8 timerNumber;
	char mode[20];
	uint16 prescaler;
	char compareMatchMode[20];
	char pwmMode[20];

}TIMER_configurationType;

void TIMER_init( TIMER_configurationType * config);
void TIMER_setCompare(uint16 compareValue);
void TIMER_setNormal(uint8 initValue);
void TIMER_setCallBack(void(*a_ptr)(void));
void TIMER_setpwm(uint8 dutyCycle);
void TIMER_stop();


#endif /* TIMER_H_ */
