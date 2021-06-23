/*
 * actuator.c
 *
 *  Created on: Jun 23, 2021
 *      Author: hesham
 */
#include"actuators.h"

void timer_set(void)
{
timer_config.timerNumber=1;
		strcpy(timer_config.mode,"compare");
		timer_config.prescaler=1024;
		TIMER_init(&timer_config);
}


void motor_run(void)
{

TIMER_setCompare(8000);
TIMER_setCallBackPtr(change_motor_dirction);


}
void change_motor_dirction(void)
{

	static uint8 count=0;
	if(count==0)
	{
		DDRB|=(1<<0)|(1<<1);
		PORTB&=~(1<<0)&~(1<<1);
		CLEAR_BIT(PORTB,1);
		SET_BIT(PORTB,0);
	}
	else if(count>=2)
{
	PORTB&=~(1<<0)&~(1<<1);

	TIMER_stop();
}
else
{
	TOGGLE_BIT(PORTB,1);
	TOGGLE_BIT(PORTB,0);
}
	count++;

}
void buzzer(void)
{

	TIMER_setCompare(60000);
	TIMER_setCallBackPtr(buzzer_call);
}
void buzzer_call(void)
{	static uint8 count=0;
if(count==0)
{
	SET_BIT(DDRC,5);
		SET_BIT(PORTC,5);
}


else if(count==8)
{
	CLEAR_BIT(PORTC,5);
	buzzer_flag=1;
	block_buzzer_scope=0;
	TIMER_stop();
}
count++;


}

