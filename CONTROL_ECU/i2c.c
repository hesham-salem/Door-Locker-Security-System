/*  module name :i2c driver
 *
 *  file name :timer.c
 *
 *  description :the source file of I2C driver
 *
 *
 *   Author: Hesham Salem
 */
#include"i2c.h"
/***************************************************************
 * 					functions definition 			*
 * *************************************************************
 */

void TWI_init(const TWI_configurationType *config)
{
	/* the equation is SCL frequency = CPU clock frequency /(16+2(TWBR)*4^prescaler */
	TWBR=((float)F_CPU/config->baudRate +16)/(2*pow(4,config->prescasler));
	 	TWSR=config->prescasler;/*store prescaler  in first 2 bits (TWPS1 and TWPS0) as other bits read only*/
	 TWAR=config->slave_address<<1;// store slave address (7bits) in the most 7 significant bits
	TWCR|=(1<<TWEN);/* enable TWI module */

}
void TWI_start(void)
{
	//make enable again to force other bits in the register to be zero
	//start bit TWSTA and clear finish current job flag TWINT by toggle it
TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
while(BIT_IS_CLEAR(TWCR,TWINT));// WAIT finish current job  flag TWINT =1
}
void TWI_stop(void)
{/*make enable again to force other bits in the register to be zero
	stop bit TWST0 and clear finish current job flag TWINT by toggle it */
TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);

//NO NEED TO WAIT TWINT flag as it  is the end of frame
}
void TWI_write(uint8 data)
{
/* store data in TWDR */
	TWDR=data;
	/*make enable again to force other bits in the register to be zero
		 clear finish current job flag TWINT by toggle it */
	TWCR=(1<<TWINT)|(1<<TWEN);

	while(BIT_IS_CLEAR(TWCR,TWINT));// WAIT finish current job  flag TWINT =1

}
uint8 TWI_read_with_ACK(void)
{/*make enable again to force other bits in the register to be zero
		 clear finish current job flag TWINT by toggle it
		 enable acknowledge bit TWEA */

	TWCR=(1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while(BIT_IS_CLEAR(TWCR,TWINT));
	//CLEAR flag before or after
	return TWDR;
}

uint8 TWI_read_with_NACK(void)
{/*make enable again to force other bits in the register to be zero
		 clear finish current job flag TWINT by toggle it*/
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(BIT_IS_CLEAR(TWCR,TWINT));// WAIT finish current job  flag TWINT =1

	return TWDR;
}
uint8 TWI_getStatus()
{	/*return bits 7:3 in status register TWSR */
	return TWSR&0XF8;
}

