/*
 * LCD.h
 *  Author: Omar Mohamed Eid
*/

#ifndef _LCD_H_
#define _LCD_H_

#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "SYSTICK.h"

/******************************************Definitions******************************************/

#define LCD GPIOB   /* Define "LCD" as a symbolic name for GPIOB */
#define PORTB 1
#define RS 0x04 /* PORTB BIT2 mask */
#define RW 0x02 /* PORTB BIT1 mask */
#define EN 0x01 /* PORTB BIT0 mask */
#define HIGH 1
#define LOW 0

/*define useful symbolic names for LCD commands */
#define clear_display     0x01
#define CursorRight   		0x06
#define Blink       			0x0F
#define Four_Bit_Mode 		0x28
#define Normal_Font_Size  0x20

/******************************************Functions Prototypes******************************************/

extern void LCD_init(void);  /* LCD initialization function */

extern void LCD_Command(unsigned char command); /*Used to send commands to LCD */

extern void LCD_Char(unsigned char data); /* Writes ASCII character */

extern void LCD_Control(unsigned char data, unsigned char control); /* Writes 4-bits */

extern void LCD_String (char *str);	/* Send string to LCD function */

#endif
