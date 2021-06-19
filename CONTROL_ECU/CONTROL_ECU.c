/*
 * Exercise1.c
 *
 * Created: 4/10/2014 9:23:41 PM
 * Author: Mohamed Tarek
 */ 

#include"CONTROL_ECU.h"
 uint8 password_stored[20];
 char check_password_stored[20]="";
 char enter_password_stored[20]="";
  uint8 password_stored_flag=0;
uint8 x =5;
  uint8 i=0;

int main(void)
{
	uint8 str[20];
	uint8 data;
	/* UART intial */
	UART_configurationType UART_config ;
			UART_config.buadRate=9600;
		UART_config.character_size=8;
		strcpy(UART_config.mode,"double speed");
		UART_init(&UART_config);
	//	UART_init();
 /*eeprom intial */
		EEPROM_init();
	//	UART_sendString("set");
		//_delay_ms(10);

    while(1)
    {
 	   	_delay_ms(100);


    	    	// first time user enter the password
    	EEPROM_readByte(0x0011,&password_stored_flag);
    	if((password_stored_flag ==0xAA)&&(i<3))
    		 {
    		UART_sendByte('d');
     	   	_delay_ms(10);

    	    	UART_receiveString(enter_password_stored);
    	   	_delay_ms(10);
    		EEPROM_readString(0x0512, check_password_stored);
    	    		_delay_ms(10);
    		if(strcmp(enter_password_stored,check_password_stored))
    		{
        	//	UART_sendByte('w');
        				i++;
    		 }
    		 }
    	else if((password_stored_flag ==0xAA)&&(i>=3))
    		UART_sendByte('B');

    	else if((password_stored_flag !=0xAA))
    	{
        	UART_sendByte('s');
        //	if(BIT_IS_SET(UCSRA,TXC))
    	UART_receiveString(password_stored);



        	_delay_ms(100);
    	EEPROM_writeString(0x0512,password_stored);
    	_delay_ms(10);
    	EEPROM_writeByte(0X0011,0xAA);
    	password_stored_flag=0xAA;

    	}

    }
}



