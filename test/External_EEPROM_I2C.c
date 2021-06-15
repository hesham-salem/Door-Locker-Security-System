/*
 * External_EEPROM_I2C.c
 *
 * Created: 3/12/2014 12:05:19 PM
 *  Author: Mohamed Tarek
 */
#include "micro_config.h"
#include "external_eeprom.h"
#include <string.h>
uint8 str[20]="tfffest";
uint8 str2[20];
int main(void)
{
	uint8 val = 0;
	
	DDRD  = 0xFF;
	PORTD = 0x00;

	/* Init EEPROM */
	EEPROM_init();

	//EEPROM_writeByte(0x0311, 0x0F); /* Write 0x0F in the external EEPROM */
	EEPROM_writeString(0x0311, str);
	_delay_ms(10);
	PORTD = 0X01;

	//EEPROM_readByte(0x0311, &val);  /* Read 0x0F from the external EEPROM */
	EEPROM_readString(0X0311, str2);
	PORTD = 0X02;

	while(1)
	{
		if(!strcmp(str,str2))
		PORTD = 0XAA; /* out the read value from the external EEPROM */
		else
			PORTD = 0X0F; /* out the read value from the external EEPROM */

	}
	return 0;
}
