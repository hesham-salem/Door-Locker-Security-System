 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.c
 *
 * Description: Source file for the External EEPROM Memory
 *
 * Author: Hesham Salem
 *
 *******************************************************************************/
#include "i2c.h"
#include "external_eeprom.h"

TWI_configurationType TWI_config;

/***************************************************************
 * 					functions definition 			*
 * *************************************************************
 */

void EEPROM_init(void)
{ /* determine the parameter which will pass to I2C driver to communicate with EEPROM */
	TWI_config.baudRate=400000; /* baud rate which EEPROM work on */
	TWI_config.prescasler=0;
	TWI_config.slave_address=0b00001011; /* the address of master when receive data from (as slave) form other slaves */

	/* passing I2C configuration structure by reference to I2C initialization function */
TWI_init(&TWI_config);
}

uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data)
{
/* send start bit */
	TWI_start();
	if(TWI_getStatus()!=TW_START) /* check the start done */
	return ERROR; /* return error if doenst send start bit */

	/* to avoid sending 3 bytes 1  byte for EEPROM address  and 2 bytes  for memory location address
	 * combine address of EEPROM address (in our case 24c16 EEPROM----->>0XA0 ) and last 3 bits of memory location address
	 * memory location address for 24c16 EEPROM is 11 bits as memory size 2kByte and the memory width is 1 K byte
	 */
	TWI_write((uint8)(0xA0|((u16addr&0X0700)>>7)));
	if(TWI_getStatus()!=TW_MT_SLA_W_ACK) /* check the master (MT) receive form slave (SLA) write (w) acknowledge (ACK) */
		return ERROR;

/* send the remaining of memory location address =11-3=8 bits */
	TWI_write((uint8)u16addr);
	if(TWI_getStatus()!=TW_MT_DATA_ACK) /* check the master (MT) receive form slave (SLA) DATA (DATA) acknowledge (ACK) */
			return ERROR;


	TWI_write(u8data);
	if(TWI_getStatus()!=TW_MT_DATA_ACK) /* check the master (MT) receive form slave (SLA) write (w) acknowledge (ACK) */
			return ERROR;

	TWI_stop(); /* end the frame */
	return SUCCESS; /* send success if the frame is completed by reach this line */
}

uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data)
{
	TWI_start();
		if(TWI_getStatus()!=TW_START)
		return ERROR;

		TWI_write((uint8)(0xA0|((u16addr&0X0700)>>7)));
		if(TWI_getStatus()!=TW_MT_SLA_W_ACK)
			return ERROR;


		TWI_write((uint8)u16addr);
		if(TWI_getStatus()!=TW_MT_DATA_ACK)
				return ERROR;

/* repeat start the frame as in this case master will read from the slave */
				TWI_start();
		if(TWI_getStatus()!=TW_REP_START) /* check the repeated start done */
						return ERROR;
/* send the address of EEPROM as slave and set the less significant bit to make master read from the slave */
		TWI_write((uint8)((0xA0)|((u16addr&0X0700)>>7)|1));
		if(TWI_getStatus()!=TW_MT_SLA_R_ACK)  /* check the master (MT) send  to slave (SLA) read (R) acknowledge (ACK) */
						return ERROR;


			*u8data=TWI_read_with_NACK(); /* read the byte */
			if(TWI_getStatus()!=TW_MR_DATA_NACK) /* check the master (MT) read the byte  from slave (SLA) read (DATA) acknowledge (ACK) */
					return ERROR;

			TWI_stop();
			return SUCCESS;

}
uint8 EEPROM_writeString(uint16 u16addr, uint8* str)
{
	/* send byte by byte until end of string (\0)
		 * and at the end of string send (\0)
		 */
	uint8 i=0;
	for( i=0;str[i]!='\0';i++)
{

/* increase the address by base +i */
	EEPROM_writeByte(u16addr+i,str[i]);
	_delay_ms(10);

}

	EEPROM_writeByte(u16addr+i,'\0');


}
uint8 EEPROM_readString(uint16 u16addr, uint8 *str)
{
	/*
	at first receive first byte then check the  null
	then enter the while loop  and receive byte by byte  until reach null
	put null '\0' at the end of string
	increment the address in EEPROM and string buffer index
	 */

	uint8 i = 0;
		EEPROM_readByte(u16addr, &str[i]);
		while(str[i]!='\0')
		{u16addr++;
			i++;
			EEPROM_readByte(u16addr, &str[i]);
		}
		str[i]='\0';

}
