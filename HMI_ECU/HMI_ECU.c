
/* *****************************************************************
 *  module name :HMI ECU
 *
 *  file name :HMI ECU.c
 *
 *  description :the source file of HMI ECU
 *
 *
 *   Author: Hesham Salem
 *   **************************************************************
 */
#include"HMI_ECU.h"
 volatile char buff[16];
 volatile uint8 key=0;
uint8 str[100]="123";
uint8 enter=1;
uint8 set_password[16]="";
uint8 confirm_password[16]="";
uint8 password[16]="";

uint8 confirm_key;
uint8 confirm_key2;

volatile uint8 data;
void intgerToString(int data);
void readPassword(uint8 *data);

UART_configurationType UART_config ;
int main()

{	SREG|=(1<<7); /*Global interrupt enable */
/*	initialize peripheral  */
	/* UART initialization */
	UART_config.buadRate=9600;
	UART_config.character_size=8;
	strcpy(UART_config.mode,"double speed");
	strcpy(UART_config.parity,"disable");
	UART_config.stop_bit_number=1;
	UART_init(&UART_config);

	/* LCD initialization */
LCD_init();


while(1)
{
	/*receive the character from CONTROL ECU which indicate to specific action */
data=UART_receiveByte();

/***************************************************************
* 		CASE 2 : first time and user should set password	*
* *************************************************************
*/
	if(data=='s')
	{ /* s:  point to set */

		while(1)
				{/* read from user the password and confirm it
				*then compare the password and its confirm
				*if they are typical send them to CONTROL ECU to store it in EEPROM
				*else request it again
				*/
				LCD_clearScreen();
				LCD_displayString("set password");
				readPassword(set_password);
				_delay_ms(500);
				LCD_clearScreen();
				LCD_displayString("confirm password");
				readPassword(confirm_password);
				_delay_ms(500);
				LCD_clearScreen();

				if(!strcmp(set_password,confirm_password))
				{	LCD_clearScreen();
					LCD_displayString("saved");
					UART_sendString(confirm_password);
					break;
					}
				}
		/*give user option to open the door */
		LCD_clearScreen();
		LCD_displayString("press enter to ");
		LCD_displayStringRowColumn(1,0 ,"  open the door");
		_delay_ms(500);
		confirm_key=KeyPad_getPressedKey();
		if(confirm_key==13)
		{
		UART_sendByte('o');
		LCD_clearScreen();
		}
	}
	/***************************************************************
	* 		CASE 0 : password already set	*
	* *************************************************************
	*/
	else if(data=='e')
	{/* read from user the password and send it to CONTROL ECU to confirm
		*if CONTROL ECU confirm the entered password
		*give the user two options open the door or set new password
		*else reruest the the password again
		*/
		while(1)
		{	LCD_clearScreen();
				LCD_displayString("enter password");
				readPassword(password);

				 	 UART_sendString(password);
				 	uint8 temp_data=UART_receiveByte();
				 	 if(temp_data=='w')
				 	 {
			 	LCD_clearScreen();
				LCD_displayString("press 1 to open");
				LCD_displayStringRowColumn(1,0 ,"2 to set password");
				confirm_key2=KeyPad_getPressedKey();
				_delay_ms(400);
						if(confirm_key2==2)
						UART_sendByte('s');
						else if(confirm_key2==1)
						UART_sendByte('o');
						break;
				 	 }
				 	 else if(temp_data=='B')
				 		 {LCD_clearScreen();
				 		 break;
				 		 }
	}
	}
	/*******************************************************************************
	* 		CASE 1 : password already set and user try enter password than 3 times	*
	* ******************************************************************************
	*/
	else if(data=='B')
	{
		LCD_clearScreen();

	}

}

}
/***************************************************************
 * 					functions definition 			*
 * *************************************************************
 */
void intgerToString(int data)
{
	/* buffer to hold acii result */
	itoa(data,buff,10); /* 10 for decimal base */
}

 void readPassword(uint8 *data)
 {
	 	while(enter==1)
	 	{
	 	key =KeyPad_getPressedKey();
	 	_delay_ms(400);
	 	if(key==13) /* enter*/
	 		break;
	 	intgerToString(key);
	 	strcat(data,buff);
	 	}
 }
