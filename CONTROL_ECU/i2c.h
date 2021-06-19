/*
 * i2c.h
 *
 *  Created on: Jun 6, 2021
 *      Author: hesham
 */

#ifndef I2C_H_
#define I2C_H_
#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"
#include <math.h>

#define  TW_START 		(0X08)
#define TW_REP_START	0X010
#define TW_MT_SLA_W_ACK  0X18
#define	TW_MT_SLA_R_ACK 0X40
#define TW_MT_DATA_ACK	0X28
#define TW_MR_DATA_ACK 	0X50
#define TW_MR_DATA_NACK	0X58

typedef struct
{
	uint32 baudRate;
	uint8 prescasler;
	uint8 slave_address;

}TWI_configurationType;


void TWI_init(const TWI_configurationType * config);
void TWI_start(void);
void TWI_stop(void);
void TWI_write(uint8 data);
uint8 TWI_read_with_ACK(void);
uint8 TWI_read_with_NACK(void);
uint8 TWI_getStatus();




#endif /* I2C_H_ */
