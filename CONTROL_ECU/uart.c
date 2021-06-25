/*  module name :uart driver
 *
 *  file name :uart.c
 *
 *  description :the source file of uart driver
 *
 *  Created on: May 24, 2021
 *
 *   Author: Hesham Salem
 */

#include"uart.h"

/***************************************************************
 * 					function definition 						*
 * *************************************************************
 */

/* configurate by passing UART  configuration structure */

void UART_init(UART_configurationType * config)
{/* put zeros into all bits in the registers */
UCSRA=0;
UCSRB=0;
UCSRC=0;
/* enables */
	if(!strcmp(config->mode,"normal"))
	{
CLEAR_BIT(UCSRA,U2X); /* disable double speed bit */
/* store buad rate in register UBRR(16bits) ---> left register 8 bits and right 8bits */
UBRRL=((F_CPU /(16*config->buadRate))-1);
UBRRH=((F_CPU /(16*config->buadRate))-1)>>8;


	}
	else if(!strcmp(config->mode,"double speed"))
	{
		SET_BIT(UCSRA,U2X);/* enable double speed bit */
		/* store buad rate in register UBRR(16bits) ---> left register 8 bits and right 8bits */
		UBRRL=((F_CPU /(8*config->buadRate))-1);
		UBRRH=((F_CPU /(8*config->buadRate))-1)>>8;

	}


/* TO enable writing on Register UCSRC (used for define the frame )as it has the same address with UBRR register */
SET_BIT(UCSRC,URSEL);
/* the UART frame parameters*/
/* character size */

switch(config->character_size)
{
case 5:
	/* UCSZ0 =0, UCSZ1=0,UCSZ2=0 */
	CLEAR_BIT(UCSRC,UCSZ0);
	CLEAR_BIT(UCSRC,UCSZ1);
	break;

case 6:
	/* UCSZ0 =0, UCSZ1=1,UCSZ2=0 */
	CLEAR_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1);
	break;
case 7:
	/* UCSZ0 =1, UCSZ=0,UCSZ2=0 */
	CLEAR_BIT(UCSRC,UCSZ1);
	SET_BIT(UCSRC,UCSZ0);
		break;
case 9:
	/* UCSZ0 =1, UCSZ1=0,UCSZ2=1 */
	SET_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1);
	SET_BIT(UCSRC,UCSZ2);


	break;

default :
	/* the default will be 8bits */
	/* UCSZ0 =1, UCSZ1=1,UCSZ2=0 */
	SET_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1);
}
switch(config->stop_bit_number)
{
default : /* STOP BIT =1 */
	SET_BIT(UCSRC,USBS);
	break;
case 2 : /* STOP BIT =2 */
	CLEAR_BIT(UCSRC,USBS);
	break;

}
if(!strcmp(config->parity,"odd"))
		{
		SET_BIT(UCSRC,UPM0);
		SET_BIT(UCSRC,UPM1);
		}
else if(!strcmp(config->parity,"even"))
		{
		SET_BIT(UCSRC,UPM0);
		CLEAR_BIT(UCSRC,UPM1);
		}
else
{
	CLEAR_BIT(UCSRC,UPM0);
	CLEAR_BIT(UCSRC,UPM1);
}
/* enable uart receive and transmit */
SET_BIT(UCSRB,RXEN);
SET_BIT(UCSRB,TXEN);
}

uint8 UART_receiveByte(void)
{
	while(BIT_IS_CLEAR(UCSRA,RXC)); /* wait until RXC  flag be 1 it means that there is data not read */

	return UDR;/* read and return RXC flag to zero */
}
void UART_sendByte(const uint8 data)
{
	UDR=data; /*store data in shift register UDR from less significant bit */
	while(BIT_IS_CLEAR(UCSRA,TXC));/*wait until send data txc =1*/
	SET_BIT(UCSRA,TXC); /*clear the flag as it doesnt clear automatically as no interrupt or ISR*/

}
void UART_sendString(uint8 *str)
{
	/* send byte by byte until end of string (\0)
	 * and at the end of string send # as defined pattern because we cant send null
	 */

	uint8 i = 0;
		while(str[i] != '\0')
		{
			UART_sendByte(str[i]);
			i++;
		}
	UART_sendByte('#');

}
void UART_receiveString(uint8 *str)
{ /*
at first receive first byte then check the  pre define pattern # may be empty string ""
then enter the while loop  and receive byte by byte  until reach pre define pattern #
and replace it with null '\0' to make string */

	uint8 i = 0;
		str[i] = UART_receiveByte();
		while(str[i] != '#')
		{
			i++;
			str[i] = UART_receiveByte();
		}
		str[i] = '\0';
}
