/*  module name :keypad driver
 *
 *  file name :keypad.h
 *
 *  description :the header file of keypad driver
 *
 *  Created on: May 24, 2021
 *
 *   Author: Hesham Salem
 */
#ifndef KEYPAD_H_
#define KEYPAD_H_
#include"std_types.h"
#include"micro_config.h"
#include"common_macros.h"

/********************************************************************
 * 					Preprocessor macros								*
 ********************************************************************
 */
/* keypad configuration for ports */

#define KEYPAD_PORT_DIR DDRA
#define	KEYPAD_PORT_OUT	PORTA
#define KEYPAD_PORT_IN PINA

/* keypad configuration for rows and columns */
#define	N_COL 4
#define	N_ROW 4

/********************************************************************
 * 					Function prototyping							*
 ********************************************************************
 */
uint8 KeyPad_getPressedKey(void);

#endif /* KEYPAD_H_ */
