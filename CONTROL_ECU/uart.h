/*  module name :uart driver
 *
 *  file name :uart.h
 *
 *  description :the header file of uart driver
 *
 *  Created on: May 24, 2021
 *
 *   Author: Hesham Salem
 */
#ifndef UART_H_
#define UART_H_
#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

/***************************************************************
 * 		structure used in UART configuration 						*
 * *************************************************************
 */
typedef struct
{
	 uint8 character_size; /* 5,6,7,8 or 9 data bits */
	 uint32 buadRate;
	 char mode[20]; /* string copy --->>("normal" or "double speed" ) */
	 char parity[20];/* 1 or 2*/
	 uint8 stop_bit_number /* string copy --->>("odd" ,"even" or " disable" ) */
}UART_configurationType;



/***************************************************************
 * 					functions prototyping 						*
 * *************************************************************
 */

void UART_init(UART_configurationType * config);
uint8 UART_receiveByte(void);
void UART_sendByte(const uint8 data);
void UART_sendString(uint8 *str);
void UART_receiveString(uint8 *str);


#endif /* UART_H_ */
