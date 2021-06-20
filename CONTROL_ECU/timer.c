/*
 * timer.c
 *
 *  Created on: Jun 11, 2021
 *      Author: hesham
 */

#include"timer.h"
static volatile  void(*g_callBackPtr)(void)= NULL_PTR;
static volatile TIMER_configurationType * configPtr;
ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr!=NULL_PTR)
		g_callBackPtr();

}
ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr!=NULL_PTR)
		g_callBackPtr();

}
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr!=NULL_PTR)
			g_callBackPtr();
}
void TIMER_init( TIMER_configurationType * config)
{configPtr=config;
	if(config->timerNumber==0)
	{
		TCCR0=0;
	switch(config->prescaler)
	{
	case 8:
		TCCR0|=(1<<CS01);
		break;
	case 64:
			TCCR0|=(1<<CS00)|(1<<CS01);
			break;
	case 256:
			TCCR0|=(1<<CS02);
			break;
	case 1024:
			TCCR0|=(1<<CS00)|(1<<CS02);
			break;
	default:
			TCCR0|=(1<<CS00);

		}

	if(!strcmp(config->mode,"compare"))
	{	TCCR0|=(1<<FOC0)|(1<<WGM01);

		if(!strcmp(config->compareMatchMode,"toggle"))
		{
		TCCR0|=(1<<COM00);
		SET_BIT(DDRB,3);
		}
		else if(!strcmp(config->compareMatchMode,"clear"))
			{
			TCCR0|=(1<<COM01);
			SET_BIT(DDRB,3);

			}
		else if(!strcmp(config->compareMatchMode,"set"))
			{
			TCCR0|=(1<<COM01)|(1<<COM00);
			SET_BIT(DDRB,3);

			}
		//enable interrupt
		TIMSK=(1<<OCIE0);

	}
	else if(!strcmp(config->mode,"normal"))
	{
		TCCR0|=(1<<FOC0);
		TIMSK=(1<<TOIE0);
	}
	else if(!strcmp(config->mode,"pwm"))
	{
		TCCR0 |=(1<<WGM00)|(1<<WGM01);
		if(!strcmp(config->pwmMode,"inverting"))
				{
				TCCR0|=(1<<COM00);
				TCCR0|=(1<<COM01);
				SET_BIT(DDRB,3);
				}
				else if(!strcmp(config->pwmMode,"non-inverting"))
					{
					TCCR0|=(1<<COM01);
					SET_BIT(DDRB,3);

					}

	}

	}
	///
	if(config->timerNumber==1)
		{
			TCCR1A=0;
			TCCR1B=0;

		switch(config->prescaler)
		{
		case 8:
			TCCR1B|=(1<<CS11);
			break;
		case 64:
				TCCR1B|=(1<<CS10)|(1<<CS11);
				break;
		case 256:
				TCCR1B|=(1<<CS12);
				break;
		case 1024:
				TCCR1B|=(1<<CS10)|(1<<CS12);
				break;
		default:
				TCCR1B|=(1<<CS10);

			}
//FOR A
		if(!strcmp(config->mode,"compare"))
		{	TCCR1A|=(1<<FOC1A);
			TCCR1B|=(1<<WGM12);
			if(!strcmp(config->compareMatchMode,"toggle"))
			{
			TCCR1A|=(1<<COM1A0);
			SET_BIT(DDRD,5);
			}
			else if(!strcmp(config->compareMatchMode,"clear"))
				{
				TCCR1A|=(1<<COM1A1);
				SET_BIT(DDRD,5);

				}
			else if(!strcmp(config->compareMatchMode,"set"))
				{
				TCCR1A|=(1<<COM1A1)|(1<<COM1A0);
				SET_BIT(DDRD,5);

				}
			//enable interrupt
			TIMSK=(1<<OCIE1A);

		}
		else if(!strcmp(config->mode,"normal"))
		{
			TCCR0|=(1<<FOC0);
			TIMSK=(1<<TOIE0);
		}
		else if(!strcmp(config->mode,"pwm"))
		{
			TCCR0 |=(1<<WGM00)|(1<<WGM01);
			if(!strcmp(config->pwmMode,"inverting"))
					{
					TCCR0|=(1<<COM00);
					TCCR0|=(1<<COM01);
					SET_BIT(DDRB,3);
					}
					else if(!strcmp(config->pwmMode,"non-inverting"))
						{
						TCCR0|=(1<<COM01);
						SET_BIT(DDRB,3);

						}

		}


	///////////////////////////

	//	TIMSK=(1<<OCIE1A);
	//		TCCR1A=(1<<FOC1A);
		//	TCCR1B=(1<<WGM12)|(1<<CS12)|(1<<CS10);


	//TCCR0=(1<<FOC0)|(1<<COM00)|(1<<CS00)|(1<<CS02);


	//enable

	sei();
}
}

void TIMER_setCompare(uint16 compareValue)
{
	switch (configPtr->timerNumber)
	{
	case 0:
		TCNT0=0;
		OCR0=compareValue;
		break;
	case 1:
		TCNT1=0;
		OCR1A=compareValue;
		break;
	}
}
void TIMER_setNormal(uint8 initValue)

{

	switch (configPtr->timerNumber)
	{
	case 0:
		TCNT0=initValue;
		break;
	case 1:
		TCNT1=initValue;
		break;


}
}
void TIMER_setpwm(uint8 dutyCycle)
{
	TCNT0=0;
	OCR0=dutyCycle;
}
void TIMER_setCallBackPtr(void(*a_ptr)(void))
{
g_callBackPtr=a_ptr;
}
void TIMER_stop()
{
	switch (configPtr->timerNumber)

{
case 0:
	TCCR0&=~(1<<CS00)&~(1<<CS01)&~(1<<CS02);
	break;
case 1:
	TCCR1B&=~(1<<CS10)&~(1<<CS11)&~(1<<CS12);
	break;

}
}
