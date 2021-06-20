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
uint8 password1[16]="";
uint8 password2[16]="";
uint8 password[16]="";

uint8 confirm_key;
uint8 confirm_key2;

volatile uint8 data;
void intgerToString(int data);
void readPassword(uint8 *data);

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

	if(data=='s')
	{

		while(1)
				{
				LCD_clearScreen();
				LCD_displayString("set password");
				readPassword(password1);
				_delay_ms(500);
				LCD_clearScreen();
				LCD_displayString("confirm password");
				readPassword(password2);
				_delay_ms(500);
				LCD_clearScreen();

				if(!strcmp(password1,password2))
				{	LCD_clearScreen();
					LCD_displayString("saved");
					UART_sendString(password2);
					break;
					}
				}
		LCD_clearScreen();
		LCD_displayString("press enter to open");
		_delay_ms(500);
		confirm_key=KeyPad_getPressedKey();
		if(confirm_key==13)
		{
		UART_sendByte('o');
		LCD_clearScreen();
		}
	}

	else if(data=='d')
	{
		while(1)
		{	LCD_clearScreen();
				LCD_displayString("enter password");
				readPassword(password);

				 	 UART_sendString(password);
				 	uint8 temp_data=UART_receiveByte();
				 	 if(temp_data=='w')
				 	 {
			 	LCD_clearScreen();
				LCD_displayString("press set 1, open 2");
				confirm_key2=KeyPad_getPressedKey();
				_delay_ms(400);
						if(confirm_key2==1)
						UART_sendByte('s');
						else if(confirm_key2==2)
						UART_sendByte('o');
						break;
				 	 }
				 	 else if(temp_data=='B')
				 		 {LCD_clearScreen();
				 		 break;
				 		 }
	}
	}

	else if(data=='B')
	{
		LCD_clearScreen();

	}

}

}

void intgerToString(int data)
{
	/* buffer to hold acii result */
	itoa(data,buff,10); /* 10 for decimal base */
}

 void readPassword(uint8 *data)
 {
	// key =KeyPad_getPressedKey();

	 	while(enter==1)
	 	{
	 	key =KeyPad_getPressedKey();
	 	_delay_ms(400);
	 	if(key==13)
	 		break;
	 	intgerToString(key);
	 	strcat(data,buff);
	 	}
 }
