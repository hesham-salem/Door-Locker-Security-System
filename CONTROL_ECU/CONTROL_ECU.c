

#include"CONTROL_ECU.h"
 uint8 password_stored[20];
 char check_password_stored[20]="";
 char enter_password_stored[20]="";
  uint8 password_stored_flag=0;
uint8 set_password_now_flag =0;
uint8 force_set =0;
  uint8 i=0;
  uint8 data_temp;
  uint8 buzzer_flag=0;
  uint8 block_buzzer_scope=1;
	void change_motor_dirction(void);

	void motor_run(void);
	void buzzer_call(void);
	void buzzer(void);

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

//timer configuration
		TIMER_configurationType timer_config;
		timer_config.timerNumber=1;
		strcpy(timer_config.mode,"compare");
		timer_config.prescaler=1024;
		TIMER_init(&timer_config);

		while(1)
    {
 	   	_delay_ms(100);

    	EEPROM_readByte(0x0011,&password_stored_flag);
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
    	else if((password_stored_flag ==0xAA)&&(i>=3)&&(set_password_now_flag==0)&&block_buzzer_scope)
    	{
    		UART_sendByte('B');
    		buzzer();
    		block_buzzer_scope=0;
    	}

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

void motor_run(void)
{

TIMER_setCompare(8000);
TIMER_setCallBackPtr(change_motor_dirction);


}
void change_motor_dirction(void)
{

	static uint8 count=0;
	if(count==0)
	{
		DDRB|=(1<<0)|(1<<1);
		PORTB&=~(1<<0)&~(1<<1);
		CLEAR_BIT(PORTB,1);
		SET_BIT(PORTB,0);
	}
	else if(count>=2)
{
	PORTB&=~(1<<0)&~(1<<1);

	TIMER_stop();
}
else
{
	TOGGLE_BIT(PORTB,1);
	TOGGLE_BIT(PORTB,0);
}
	count++;

}
void buzzer(void)
{

	TIMER_setCompare(60000);
	TIMER_setCallBackPtr(buzzer_call);
}
void buzzer_call(void)
{	static uint8 count=0;
if(count==0)
{
	SET_BIT(DDRC,5);
		SET_BIT(PORTC,5);
}


else if(count==8)
{
	CLEAR_BIT(PORTC,5);
	buzzer_flag=1;
	block_buzzer_scope=1;
	TIMER_stop();
}
count++;


}

