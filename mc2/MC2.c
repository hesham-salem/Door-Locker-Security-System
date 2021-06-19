/*
 * MC2.c
 *
 * Created: 4/10/2014 11:23:48 PM
 * Author: mohamed tarek
 */ 

#include "uart.h"
#include "lcd.h"
#include<string.h>
#define M2_READY 0x10
uint8 str[100]="";
int main(void)
{

	UART_init(); // initialize UART driver
	LCD_init(); // initialize LCD driver
	//UART_sendByte(M2_READY); // MC2 is ready
//	UART_receiveString(Str); // receive the string
//	LCD_displayString(Str); // display the string on LCD
	//UART_sendByte('k');
    while(1)
    {

    	UART_sendByte('a');
    //	if(BIT_IS_SET(UCSRA,UDRE))

    	UART_receiveString(&str);


if(!strcmp(str,"I am Micro1#"))
	{UART_sendByte('g');
	UART_sendString("good");
	}		    		 // receive the string
    		    		 // display the string on LCD
    		        	_delay_ms(100);
    		        	LCD_displayString(str);

    }
}
