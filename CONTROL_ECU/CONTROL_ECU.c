

#include"CONTROL_ECU.h"
#include"actuators.h"


uint8 password_stored[20];
char check_password_stored[20]="";
char enter_password_stored[20]="";
uint8 password_stored_flag=0;
uint8 set_password_now_flag =0;
uint8 force_set =0;
uint8 i=0;
uint8 data_temp;


int main(void)
{
/*	initialize peripheral  */

	/* UART initialization */
		UART_configurationType UART_config ;
		UART_config.buadRate=9600;
		UART_config.character_size=8;
		strcpy(UART_config.mode,"double speed");
		UART_init(&UART_config);

	/*EEPROM initialization */
		EEPROM_init();

	/* TIMER configuration which set in acturators module */
		timer_set();

		while(1)
    {

 	   	_delay_ms(100); /* delay to force UART in control_ECU synchronize with HMI_ECU */


 	   	/*check on a password stored flag if it equal predefine pattern=0xAA in specified address 0x0011
 	  */
    	EEPROM_readByte(0x0011,&password_stored_flag);

/***************************************************************
* 		CASE 0 : password already set	*
* *************************************************************
*/
    	if(((password_stored_flag ==0xAA)&&(i<3)&&(set_password_now_flag==0))||buzzer_flag)
    		 {
    		UART_sendByte('d');
     	   	_delay_ms(10);

    	    	UART_receiveString(enter_password_stored);
    	   	_delay_ms(10);
    		EEPROM_readString(0x0512, check_password_stored);
    	    		_delay_ms(10);
    		if(!strcmp(enter_password_stored,check_password_stored))
    		{
        		UART_sendByte('w');
        		data_temp=UART_receiveByte();
        		if(data_temp=='s')
        			force_set=1;
        		else if(data_temp=='o')
        		{
        			 motor_run();
        		}
    		 }
    		else
    		{
    			UART_sendByte('u');
				i++;
    		}
    		 }

/*******************************************************************************
* 		CASE 1 : password already set and user try enter password than 3 times	*
* ******************************************************************************
*/

    	else if((password_stored_flag ==0xAA)&&(i>=3)&&(set_password_now_flag==0)&&(!block_buzzer_scope))
    	{
    		UART_sendByte('B');
    		buzzer();
    		block_buzzer_scope=1;
    	}

    	/***************************************************************
    	* 		CASE 0 : first time and user should set password	*
    	* *************************************************************
    	*/

    	if(((password_stored_flag !=0xAA)&&(set_password_now_flag==0))||force_set)
    	{
        	UART_sendByte('s');
    	UART_receiveString(password_stored);
        	_delay_ms(100);
    	EEPROM_writeString(0x0512,password_stored);
    	_delay_ms(10);
    	EEPROM_writeByte(0X0011,0xAA);
    	password_stored_flag=0xAA;
    	set_password_now_flag=0xAA;
    	if(UART_receiveByte()=='o')
    		 motor_run();

    	}

    }
}

