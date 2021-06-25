
/*  module name :control ECU
 *
 *  file name :control ECU.c
 *
 *  description :the source file of control ECU
 *
 *
 *   Author: Hesham Salem
 */
#include"CONTROL_ECU.h"
#include"actuators.h"


uint8 password_stored[20];
char check_password_stored[20]="";
char enter_password_stored[20]="";
uint8 password_stored_flag=0;
uint8 set_password_now_flag =0;
uint8 force_set =0;
uint8 count_password_tring=0;
uint8 data_temp;


int main(void)
{
	SREG|=(1<<7); /*Global interrupt enable */
/*	initialize peripheral  */

	/* UART initialization */
		UART_configurationType UART_config ;
		UART_config.buadRate=9600;
			UART_config.character_size=8;
			strcpy(UART_config.mode,"double speed");
			strcpy(UART_config.parity,"disable");
			UART_config.stop_bit_number=1;
			UART_init(&UART_config);
	/*EEPROM initialization */
		EEPROM_init();

	/* TIMER configuration which set in actuators module */
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
    	if(((password_stored_flag ==0xAA)&&(count_password_tring<3)&&(set_password_now_flag==0)&&(!block_buzzer_scope)))
    		 {
/* condition to enter this case password
 * is stored in EEPROM and
 *  not exceeded 3 times trying to enter password
 * user dosent set the password now as no need to check password
 * waiting 1 minutes until finishing waring
 */
    		UART_sendByte('e'); /* send 'e' point to enter password */
     	   	_delay_ms(10);
     	   	/* receive entered password and compare with that was stored in EEPROM */
    	    	UART_receiveString(enter_password_stored);
    	   	_delay_ms(10);
    		EEPROM_readString(0x0512, check_password_stored);
    	    		_delay_ms(10);
    		if(!strcmp(enter_password_stored,check_password_stored))
    		{ /* if entered and stored password are typical
    		 	give user 2 option by sending 'w':
    		 	open door (o)
    		 	reset the password (reset the password (s)
    		 	*/
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
    			/* count how many user try enter the password */
    			count_password_tring++;
    		}
    		 }

/*******************************************************************************
* 		CASE 1 : password already set and user try enter password than 3 times	*
* ******************************************************************************
*/

    	else if((password_stored_flag ==0xAA)&&(count_password_tring>=3)&&(set_password_now_flag==0)&&(!block_buzzer_scope))
    	{
    		/* condition to enter this case password
    		 * is stored in EEPROM and
    		 *   exceeded 3 times trying to enter password
    		 * user dosent set the password now as no need to check password
    		 * waiting 1 minutes until finishing waring
    		 */


    		UART_sendByte('B'); /* send 'B' to HMI ECU TO Clear the screan */
    		buzzer(); /* run buzzer warning */
    		block_buzzer_scope=1; /* block this scope until timer spend 1 minute and the timer ISR will return it to zero*/
    		count_password_tring=0; /*restart the operation */
    	}

    	/***************************************************************
    	* 		CASE 2 : first time and user should set password	*
    	* *************************************************************
    	*/

    	if(((password_stored_flag !=0xAA)&&(set_password_now_flag==0))||force_set)
    	{
    		/* condition to enter this case
    		 *  password is not stored in EEPROM
    		 * user dosent set the password now as no need to reset the password
    		 */

        	UART_sendByte('s'); /*send 's' to tell HMI ECU that CONTROL ECU  ready to store the new password */
    	UART_receiveString(password_stored);
        	_delay_ms(100);
    	EEPROM_writeString(0x0512,password_stored); /* overwrite on old password  in EEPROM*/
    	_delay_ms(10);
    	EEPROM_writeByte(0X0011,0xAA); /* write in password_stored_flag address in EEPROM */
    	password_stored_flag=0xAA;/*change password_stored_flag  in data segment in ram */
    	set_password_now_flag=0xAA;  /* prevent the program from requesting from user reenter or reset password */
    	if(UART_receiveByte()=='o') /* give user option to open the door */
    		 motor_run();

    	}

    }
}

