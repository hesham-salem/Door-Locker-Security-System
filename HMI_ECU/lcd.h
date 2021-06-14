/********************************************************
 * Module : LCD
 *
 * file name : lcd.h
 *
 * Description : header file for LCD driver
 *
 *  Created on: May 22, 2021
 *
 *      Author: Hesham Salem
 *
 *********************************************************************
 */

#ifndef LCD_H_
#define LCD_H_

#include"common_macros.h"
#include"micro_config.h"
#include"std_types.h"
/********************************************************************
* 							Preprosessor Macros						*
* *******************************************************************
 */
/* LCD HW Pins */
#define RS 4
#define READWRITE 5
#define LCD_ENABLE 6
#define LCD_CTRL_PORT PORTD
#define LCD_CTRL_PORT_DIR DDRD
#define LCD_DATA_PORT PORTC
#define LCD_DATA_PORT_DIR DDRC

/* LCD Command*/
#define DISPLAY_CURSOR_OFF 0X0C
#define CLEAR_COMMAND 0X01
#define FUNCTION_SET_8_BIT_2LINE 0X38
/************************************************************************
 * 						Functions prototyping							*
 ************************************************************************
 */

void LCD_init(void);
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(uint8 *str);
void LCD_goToRowColum(uint8 row,uint8 col);
void LCD_displayStringRowColumn(uint8 row, uint8 col ,uint8 *str);
void LCD_clearScreen();
void LCD_intgerToString(int data);




#endif /* LCD_H_ */
