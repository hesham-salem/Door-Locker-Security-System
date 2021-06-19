/*
 * MC1.c
 *
 * Created: 4/10/2014 11:21:37 PM
 * Author: mohamed tarek
 */ 

#include "uart.h"

#define M2_READY 0x10
uint8 str[100]="";
uint8 x;
int main(void)
{
	UART_init(); // initialize UART
//	while(UART_recieveByte() != M2_READY){} // wait until MC2 is ready

    while(1)
    {		//	UART_sendString("good");

    	x=UART_recieveByte();
    if(x=='a')
    	UART_sendString("I am Micro1#");
   else if(UART_recieveByte()=='g')
   // else if(5==1)
    	   	UART_receiveString(&str);

    		 // send the required string to MC2

    }
}
