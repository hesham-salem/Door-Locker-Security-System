/*
 * HMI_ECU.C
 *
 *  Created on: Jun 13, 2021
 *      Author: hesham
 */

#include"HMI_ECU.h"
 volatile char buff[16];
 volatile uint8 key=0;
uint8 str[100]="123";
uint8 enter=1;
uint8 strrr[16]="";
volatile uint8 data;
void intgerToString(int data);
void readPassword();

UART_configurationType UART_config ;
int main()
{
	UART_config.buadRate=9600;
	UART_config.character_size=8;
	strcpy(UART_config.mode,"double speed");


LCD_init();
UART_init(&UART_config);
//UART_init();
//UART_sendByte('q');
//UART_sendString("hesham");

while(1)
{
data=UART_receiveByte();

LCD_displayCharacter('loop');

	if(data=='d')
	{
		LCD_clearScreen();
		LCD_displayString("set password");
		readPassword();
		 	 UART_sendString(strrr);

	 	LCD_clearScreen();
		LCD_displayString(strrr);


	}

	else if(data=='s')
	{
		LCD_clearScreen();
		LCD_displayString("enter password  ");
		readPassword();
		 UART_sendString(strrr);
		LCD_clearScreen();
		LCD_displayString(strrr);
	}
	else if(data=='B')
	{
		LCD_clearScreen();
		LCD_displayString("bazzer  ");
	}

}

}

void intgerToString(int data)
{
	/* buffer to hold acii result */
	itoa(data,buff,10); /* 10 for decimal base */
}

 void readPassword()
 {
	// key =KeyPad_getPressedKey();

	 	while(enter==1)
	 	{
	 	key =KeyPad_getPressedKey();
	 	_delay_ms(400);
	 	if(key==13)
	 		break;
	 	intgerToString(key);
	 	strcat(strrr,buff);
	 	}
 }
