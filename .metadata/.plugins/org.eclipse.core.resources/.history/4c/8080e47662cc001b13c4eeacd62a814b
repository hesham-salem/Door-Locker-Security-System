/*  module name :keypad driver
 *
 *  file name :keybad.c
 *
 *  description :the source file of keypad driver
 *
 *  Created on: May 24, 2021
 *
 *   Author: Hesham Salem
 */

#include"keypad.h"

/****************************************************
 * 				functions prototyping (private)		*
 ****************************************************
 */
#if(N_COL==3)
/* function to mapping the the switch position in keypad 4x3 to
 * corresponding actual number
 */
 uint8 KeyPad_4x3_adjustSwitchNumber(uint8 a_number);
#elif(N_COL==4)
/* function to mapping the the switch position in keypad 4x4 to
 * corresponding actual number
 */
static uint8 KeyPad_4x4_adjustSwitchNumber(uint8 a_number);
#endif
/***************************************************************
 * 					function definition 						*
 * *************************************************************
 */

uint8 KeyPad_getPressedKey(void) {
	uint8 row, col;
	while(1)
	{
	for (col = 0; col < N_COL; col++) {
		/* set the specified column in this trace output pin and the first 4 pins as input */
		KEYPAD_PORT_DIR = (0b00010000 << col);
		/* put on the specified column in this trace output pin 0 and  make the first 4 pins as pull up */
		KEYPAD_PORT_OUT = (~(0b00010000 << col));
		for (row = 0; row < N_ROW; row++) /* loop for rows */
		{
			if (BIT_IS_CLEAR(KEYPAD_PORT_IN, row))/* if the switch is pressed in this row */
			{
				#if(N_COL==3)
				return KeyPad_4x3_adjustSwitchNumber((row * N_COL) + col + 1);
				#elif(N_COL==4)
				return KeyPad_4x4_adjustSwitchNumber((row * N_COL) + col + 1);
				#endif
			}
		}
	}

}
}

#if(N_COL==3)
 uint8 KeyPad_4x3_adjustSwitchNumber(uint8 a_number) {


	switch (a_number) {
	case 10:
		return '*';
	case 11:
		return 0;
	case 12:
		return '#';
	default:
		return a_number;
	}
 }


#elif(N_COL==4)

static uint8 KeyPad_4x4_adjustSwitchNumber(uint8 a_number) {
	switch (a_number) {
	case 1:
		return 7;
	case 2:
		return 8;
	case 3:
		return 9;
	case 4:
		return '/';
	case 5:
		return 4;
	case 6:
		return 5;
	case 7:
		return 6;
	case 8:
		return '*';
	case 9:
		return 1;
	case 10:
		return 2;
	case 11:
		return 3;
	case 12:
		return '-';
	case 13:
		return 13;
	case 14:
		return 0;
	case 15:
		return '=';
	case 16:
		return '+';

	}
}
#endif
