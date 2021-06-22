/*  module name :timer driver
 *
 *  file name :timer.c
 *
 *  description :the source file of timer driver
 *
 *
 *   Author: Hesham Salem
 */

#include"timer.h"

/* initialize callBack Pointer to null to avoid runtime error */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;
/* make timer configuration pointer global to used in set functions */
static volatile TIMER_configurationType *configPtr;

/***************************************************************
 * 		Interrupt Service Routine functions definition 						*
 * *************************************************************
 */
/*ISR function work with timer 0 compare match mode */
ISR(TIMER0_COMP_vect) {
	if (g_callBackPtr != NULL_PTR) /* check that callback function address is passed */
		g_callBackPtr();/* point to callBack function */

}
/*ISR function work with timer 0 normal mode */
ISR(TIMER0_OVF_vect) {
	if (g_callBackPtr != NULL_PTR)
		g_callBackPtr();

}
/*ISR function work with timer 1 normal mode */
ISR(TIMER1_OVF_vect) {
	if (g_callBackPtr != NULL_PTR)
		g_callBackPtr();

}
/*ISR function work with timer 1A compare match mode */
ISR(TIMER1_COMPA_vect) {
	if (g_callBackPtr != NULL_PTR)
		g_callBackPtr();
}
/*ISR function work with timer 2 compare match mode */
ISR(TIMER2_COMP_vect) {
	if (g_callBackPtr != NULL_PTR)
		g_callBackPtr();

}
/*ISR function work with timer 2 normal mode */
ISR(TIMER2_OVF_vect) {
	if (g_callBackPtr != NULL_PTR)
		g_callBackPtr();
}

/***************************************************************
 * 					functions definition 			*
 * *************************************************************
 */




/* configurate by passing timer  configuration structure */
void TIMER_init(TIMER_configurationType *config) {
	configPtr = config; /* make passed configuration global */
/***************************************************************
* 					TIMER number
* 					0-TIMER0 (8 bits)
* 					1-TIMER1	(16bits +2 output compare pins )
* 					2-TIMER2	(8 bits +more prsecaler )					*
* *************************************************************
*/



/***************************************************************
* 						0	TIMER0		*
* *************************************************************/
	if (config->timerNumber == 0) {
		TCCR0 = 0; /* put zeros into all bits in the register */
		switch (config->prescaler) {
		case 8:
			TCCR0 |= (1 << CS01); /*CS00=0  CS01=1 CS02=0  */
			break;
		case 64:
			TCCR0 |= (1 << CS00) | (1 << CS01); /*CS00=1  CS01=1 CS02=0  */
			break;
		case 256:
			TCCR0 |= (1 << CS02); /*CS00=0  CS01=0 CS02=02  */
			break;
		case 1024:
			TCCR0 |= (1 << CS00) | (1 << CS02); /*CS00=1  CS01=0 CS02=1  */
			break;
		default:/* the default case work scale 1:1 even the prescaler member not determine */
			TCCR0 |= (1 << CS00); /*CS00=1  CS01=0 CS02=0  */

		}
/***************************************************************
 * 					0-0 select the mode for TIMER0	*
* *************************************************************
*/
		if (!strcmp(config->mode, "compare"))
		{
			TCCR0 |= (1 << FOC0) | (1 << WGM01);
			/*
			 * FOC0=1 for non PWM mode
			 * select compare mode --->> WGM01=1 and WGM00=0
			 */


/****************************************************
 * 		0-1 compare match output mode for TIMER0	*
 * ***************************************************
 */


				if (!strcmp(config->compareMatchMode, "toggle")) {
					TCCR0 |= (1 << COM00); /*COM00=1 AND COM01=0 */
					SET_BIT(DDRB, 3); /*make OCO AS OUTPUT BIT */
				} else if (!strcmp(config->compareMatchMode, "clear")) {
					TCCR0 |= (1 << COM01); /*COM00=0 AND COM01=1 */
					SET_BIT(DDRB, 3);
				} else if (!strcmp(config->compareMatchMode, "set")) {
					TCCR0 |= (1 << COM01) | (1 << COM00); /*COM00=1 AND COM01=1 */
					SET_BIT(DDRB, 3);
				}
				/* the default case will be normal port operation OCO disconnected
				enable interrupt for compare mode */
				TIMSK = (1 << OCIE0);
			}


/****************************************************
 * 		0-2 normal  mode for TIMER0		    *
 * ***************************************************
 */

		else if (!strcmp(config->mode, "normal"))
			{
			/*
			 * FOC0=1 for non PWM mode
			 * select normal mode --->> WGM01=0 and WGM00=0
			 */
			TCCR0 |= (1 << FOC0);
			TIMSK = (1 << TOIE0);

			}
/****************************************************
 * 			0-3 PWM  mode for TIMER0	   *
 * ***************************************************
								 */
		else if (!strcmp(config->mode, "pwm")) {
			/*
			 * FOC0=0 for  PWM mode
			 * select PWM mode --->> WGM01=1 and WGM00=1
			 */
			TCCR0 |= (1 << WGM00) | (1 << WGM01);


			if (!strcmp(config->pwmMode, "inverting")) {
				/* COM00=1 and COM01=1 */
				TCCR0 |= (1 << COM00);
				TCCR0 |= (1 << COM01);
				SET_BIT(DDRB, 3);/*make OCO AS OUTPUT BIT */
			} else if (!strcmp(config->pwmMode, "non-inverting")) {
				/* COM00=0 and COM01=1 */
				TCCR0 |= (1 << COM01);
				SET_BIT(DDRB, 3);

			}

		}
	}

/****************************************************
 * 					1 TIMER1				*
* ***************************************************
*/

	if (config->timerNumber == 1) {
		/* put zeros into all bits in the registers */
	}
		TCCR1A = 0;
		TCCR1B = 0;

		switch (config->prescaler) {
		case 8:
			TCCR1B |= (1 << CS11);/*CS10=0  CS11=1 CS12=0  */
			break;
		case 64:
			TCCR1B |= (1 << CS10) | (1 << CS11); /*CS10=1  CS11=1 CS12=0  */
			break;
		case 256:
			TCCR1B |= (1 << CS12);/*CS10=0  CS11=0 CS12=1  */
			break;
		case 1024:
			TCCR1B |= (1 << CS10) | (1 << CS12);/*CS10=1  CS11=1 CS12=1  */
			break;
		default:/* the default case work scale 1:1 even the prescaler member not determine */
			TCCR1B |= (1 << CS10); /*CS10=1  CS11=0 CS12=0  */

		}

/***************************************************************
	 * 					1.0 select the mode for TIMER1	*
* *************************************************************
*/



/****************************************************
* 		1-1 compare match output mode for TIMER1 A	*
* ***************************************************
*/
		if (!strcmp(config->mode, "compare")) {
			/*
			 * FOC1=1 for non PWM mode
			 * select compare mode --->> /* WGM10=0 ,  WGM11=0 , WGM12=1 and WGM13=0 */
			TCCR1A |= (1 << FOC1A);
			TCCR1B |= (1 << WGM12);
			if (!strcmp(config->compareMatchMode, "toggle")) {
				TCCR1A |= (1 << COM1A0); /*COM1A0=1 AND COM1A1=0 */
				SET_BIT(DDRD, 5);/*make OCO AS OUTPUT BIT */
			} else if (!strcmp(config->compareMatchMode, "clear")) {
				TCCR1A |= (1 << COM1A1);/*COM1A0=0 AND COM1A1=1 */
				SET_BIT(DDRD, 5);

			} else if (!strcmp(config->compareMatchMode, "set")) {
				TCCR1A |= (1 << COM1A1) | (1 << COM1A0);/*COM1A0=1 AND COM1A1=1 */
				SET_BIT(DDRD, 5);

			}
			/* the default case will be normal port operation OCO disconnected
							enable interrupt for compare mode */
			TIMSK = (1 << OCIE1A);
/****************************************************
* 		1-2 normal  mode for TIMER1		      *
* ***************************************************
*/
		} else if (!strcmp(config->mode, "normal"))
		{
			/*
			 * FOC0=1 for non PWM mode
			 * select normal mode --->> WGM11=0 and WGM10=0
						 */
			TCCR1A |= (1 << FOC1A);
			TIMSK = (1 << TOIE1);


/****************************************************
 * 			1-3 PWM  mode for TIMER1 A		  *
 * ***************************************************/
		} else if (!strcmp(config->mode, "pwm")) {
			/* WGM10=1 ,  WGM11=1 , WGM12=1 and WGM13=1 */
			TCCR0 |= (1 << WGM10) | (1 << WGM11)| (1 << WGM12)| (1 << WGM13);
			if (!strcmp(config->pwmMode, "inverting")) {
				TCCR0 |= (1 << COM1A0);/* COM1A0=1 and COM1A1=1 */
				TCCR0 |= (1 << COM1A1);
				SET_BIT(DDRB, 3);
			} else if (!strcmp(config->pwmMode, "non-inverting")) {
				TCCR0 |= (1 << COM1A1);/* COM1A0=0 and COM1A1=1 */
				SET_BIT(DDRB, 3);/*make OCO AS OUTPUT BIT */

			}

		}
/***************************************************************
* 						2	TIMER2						*
 * *************************************************************/
		if (config->timerNumber == 2) {
			TCCR2 = 0;/* put zeros into all bits in the register */
			switch (config->prescaler) {
			case 8:
				TCCR2 |= (1 << CS21);/*CS20=0  CS21=1 CS22=0  */
				break;
			case 32:
				TCCR2 |= (1 << CS20) | (1 << CS21);/*CS20=1  CS21=0 CS22=0  */
				break;
			case 64:
				TCCR2 |= (1 << CS22);/*CS20=0  CS21=0 CS22=1  */
				break;
			case 128:
				TCCR2 |= (1 << CS20) | (1 << CS22);/*CS20=1  CS21=0 CS22=1  */
				break;
			case 256:
				TCCR2 |= (1 << CS21) | (1 << CS22);/*CS20=0  CS21=1 CS22=1  */
				break;
			case 1024:
				TCCR2 |= (1 << CS20) | (1 << CS21) | (1 << CS22);/*CS20=1  CS21=1 CS22=1  */
				break;
			default:/* the default case work scale 1:1 even the prescaler member not determine */
				TCCR2 |= (1 << CS20);/*CS20=1  CS21=0 CS22=0  */

			}

/************************************************************
* 					2.0 select the mode for TIMER2		*
* ***********************************************************
*/



/****************************************************
* 		2-1 compare match output mode for TIMER2	*
 * ***************************************************
					 */
			if (!strcmp(config->mode, "compare")) {
				/*
				 * FOC2=1 for non PWM mode
				 * select compare mode --->> WGM21=1 and WGM20=0
				 */
				TCCR2 |= (1 << FOC2) | (1 << WGM21);

				if (!strcmp(config->compareMatchMode, "toggle")) {
					TCCR2 |= (1 << COM20);/*COM20=1 AND COM21=0 */
					SET_BIT(DDRD, 7);/*make OCO AS OUTPUT BIT */
				} else if (!strcmp(config->compareMatchMode, "clear")) {
					TCCR2 |= (1 << COM21);/*COM20=0 AND COM21=1 */
					SET_BIT(DDRD, 7);

				} else if (!strcmp(config->compareMatchMode, "set")) {
					TCCR2 |= (1 << COM21) | (1 << COM20);/*COM20=1 AND COM21=1 */
					SET_BIT(DDRD, 7);

				}
				/* the default case will be normal port operation OCO disconnected
											enable interrupt for compare mode */
				TIMSK = (1 << OCIE2);
			}

/****************************************************
* 		2-2 normal  mode for TIMER2		     *
 * ***************************************************
					 */
			else if (!strcmp(config->mode, "normal")) {
				/*
				 * FOC2=1 for non PWM mode
				 * select normal mode --->> WGM21=0 and WGM20=0
				*/
				TCCR2 |= (1 << FOC2);
				TIMSK = (1 << TOIE2); /*enable interrupt for normal mode */


/****************************************************
 * 			2-3 PWM  mode for TIMER2	     *
 * ***************************************************/

			} else if (!strcmp(config->mode, "pwm")) {
				/*
				 * FOC2=0 for  PWM mode
				 * select PWM mode --->> WGM21=1 and WGM20=1
				 */

				TCCR2 |= (1 << WGM20) | (1 << WGM21);
				if (!strcmp(config->pwmMode, "inverting")) {
					/* COM20=1 and COM21=1 */
					TCCR2 |= (1 << COM20);
					TCCR2 |= (1 << COM21);
					SET_BIT(DDRD, 7);
				} else if (!strcmp(config->pwmMode, "non-inverting")) {
					/* COM20=0 and COM21=1 */
					TCCR2 |= (1 << COM21);
					SET_BIT(DDRD, 7);/*make OCO AS OUTPUT BIT */

				}

			}

		}
		/* global interrupt enable */
		sei();
	}


/**********************************************************
 * 			 setting functions definition 			*
 * *******************************************************
 */

/* function to set compare value for compare mode */
void TIMER_setCompare(uint16 compareValue) {
	switch (configPtr->timerNumber) {
	case 0:/* timer number*/
		TCNT0 = 0;/* initial value */
		OCR0 = compareValue; /*compare value */
		break;
	case 1:
		TCNT1 = 0;
		OCR1A = compareValue;
		break;
	case 2:
		TCNT2 = 0;
		OCR2 = compareValue;
		break;
	}
}
/* function to set initial value in normal mode */
void TIMER_setNormal(uint8 initValue)
{
	switch (configPtr->timerNumber) {
	case 0:
		TCNT0 = initValue;
		break;
	case 1:
		TCNT1 = initValue;
		break;
	case 2:
		TCNT2 = initValue;
		break;

	}
	/* function to set duty cycle value in PWM mode */
}
void TIMER_setpwm(uint8 dutyCycle) {
	switch (configPtr->timerNumber) {

	case 0:
		TCNT0 = 0;
		OCR0 = dutyCycle;
		break;
	case 1:
		TCNT1 = 0;
		OCR1A = dutyCycle;
		break;
	case 2:
		TCNT2 = 0;
		OCR2 = dutyCycle;
		break;
	}
}
/* function to get adress of call back funtion to passing it for ISR */
void TIMER_setCallBackPtr(void (*a_ptr)(void)) {
	g_callBackPtr = a_ptr; /*g_callBackPtr is shared global variable */
}
/* function to stop the running timer */
void TIMER_stop() {
	switch (configPtr->timerNumber)

	{
	case 0:
		TCCR0 &= ~(1 << CS00) & ~(1 << CS01) & ~(1 << CS02);
		break;
	case 1:
		TCCR1B &= ~(1 << CS10) & ~(1 << CS11) & ~(1 << CS12);
		break;
	case 2:
		TCCR2 &= ~(1 << CS20) & ~(1 << CS21) & ~(1 << CS22);
		break;
	}
}
