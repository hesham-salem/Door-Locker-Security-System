/*  module name :i2c driver
 *
 *  file name :timer.c
 *
 *  description :the header file of I2C driver
 *
 *
 *   Author: Hesham Salem
 */

#ifndef I2C_H_
#define I2C_H_
#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"
#include <math.h>

/********************************************************************
 * 					Preprocessor macros								*
 ********************************************************************
 */
/* status register's bits */
#define  TW_START 		(0X08)
#define TW_REP_START	0X010
#define TW_MT_SLA_W_ACK  0X18
#define	TW_MT_SLA_R_ACK 0X40
#define TW_MT_DATA_ACK	0X28
#define TW_MR_DATA_ACK 	0X50
#define TW_MR_DATA_NACK	0X58

/***************************************************************
 * 		structure used in timer configuration 				*
 * *************************************************************
 */
typedef struct
{
	uint32 baudRate; /* normal mode 100kb/s is the most common , fast mode 400 kb/s ,fast mode plus 1Mb/s or high speed mode 3.4Mb/s*/
	uint8 prescasler; /*1 ,4 ,16 or 64*/
	uint8 slave_address;/* 7bits address */

}TWI_configurationType;

/********************************************************************
 * 					Function prototyping							*
 ********************************************************************
 */
void TWI_init(const TWI_configurationType * config);
void TWI_start(void);
void TWI_stop(void);
void TWI_write(uint8 data);
uint8 TWI_read_with_ACK(void);
uint8 TWI_read_with_NACK(void);
uint8 TWI_getStatus();




#endif /* I2C_H_ */
