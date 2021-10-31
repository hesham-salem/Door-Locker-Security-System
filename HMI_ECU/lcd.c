/***********************************************************************
 * module name :LCD
 *test for my
 * file name : lcd.c
 *
 * description : source file for LCD driver
 *
 * Created on: May 22, 2021
 *
*  Author: Hesham Salem
 ***********************************************************************
 */
#include"lcd.h"

/***********************************************************************
 * 								Functions Definitions				   *
 ***********************************************************************
 */

void LCD_init(void)
{
LCD_CTRL_PORT_DIR |=(1<<RS)|(1<<READWRITE)|(1<<LCD_ENABLE);/* configure control port pins(RS ,R/W ,ENABLE) AS OUTPUT*/
LCD_DATA_PORT_DIR=0XFF; /* configure the data port as output port */
LCD_sendCommand(FUNCTION_SET_8_BIT_2LINE); /* using 2 lines + LCD 8 bit mode + 5*7 dot  display mode*/
LCD_sendCommand(DISPLAY_CURSOR_OFF);
LCD_sendCommand(CLEAR_COMMAND);

}

void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RS);/* instruction mode RS =0*/
	CLEAR_BIT(LCD_CTRL_PORT,READWRITE); /* write data to LCD so readwrite=0*/
	_delay_ms(1);/* delay for prossing tas=50ns*/
	SET_BIT(LCD_CTRL_PORT,LCD_ENABLE); /*enable LCD so enable pin =1*/
	_delay_ms(1); /*delay for processing Tpw - Tdws = 190ns */
	LCD_DATA_PORT=command;/* out the required command to the data bus D0--->D7*/
	_delay_ms(1);/* delay for processing command setup time tdsw =60ns */
	CLEAR_BIT(LCD_CTRL_PORT,LCD_ENABLE); /* disable LCD so enable pin =0 */
	_delay_ms(1); /* delay for processing hold time th=10ns */

}
void LCD_displayCharacter(uint8 data)
{
	SET_BIT(LCD_CTRL_PORT,RS); /* data mode so RS =1*/
	_delay_us(1);/*delay processing RS set time tas=40ns */
	CLEAR_BIT(LCD_CTRL_PORT,READWRITE); /*write data to LCD so READWRITE =0 */
	_delay_us(1);/* delay processing R/W set time tas =40ns */
	SET_BIT(LCD_CTRL_PORT,LCD_ENABLE); /* enable LCD so enable =1 */
	_delay_ms(1); /*delay for processing Tpw - Tdws = 190ns*/
	PORTC=data; /* out the required data to output data bus D0-->D7 */
	_delay_ms(1);/* delay processing command setup time tdsw=60ns */
	CLEAR_BIT(LCD_CTRL_PORT,6); /* disable LCD so enable pin =0*/
	_delay_ms(1); /* delay for processing hold time th =10ns*/
}
void LCD_displayString(uint8 *str)
{
	for(uint8 i=0 ;str[i]!='\0';i++)
	LCD_displayCharacter( str[i]);
}
void LCD_goToRowColumn(uint8 row,uint8 col)
{	/* first of all calculate the required address */
	uint8 address;
	switch(row)
	{
	case 0:
		address=col;
		break;
	case 1:
		address=0x40+col;
		break;
	case 2:
		address=0x10+col;
		break;
	case 3:
		address=0x50+col;
		break;
		}
	/* pass the specific address to the LCD
	 * to change the address you should add 0x80 to address
	 */
	LCD_sendCommand(address|0x80);
}
void LCD_displayStringRowColumn(uint8 row, uint8 col ,uint8 *str)
{
	LCD_goToRowColumn( row, col);/* go to the required position*/
	LCD_displayString(str);/* display the string*/
}
void LCD_clearScreen()
{
	LCD_sendCommand(CLEAR_COMMAND);/* clear display*/
}
void LCD_intgerToString(int data)
{
	char buff[16];/* buffer to hold acii result */
	itoa(data,buff,10); /* 10 for decimal base */
	LCD_displayString(buff);
}
