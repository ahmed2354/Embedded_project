/*
 * UART.h
 *  Author: Marium Waleed, Mai Mohamed, Menna Hassan
*/

#ifndef  __UART_H__
#define __UART_H__

#include <stdint.h>
#include "GPS.h"
#include "tm4c123gh6pm.h"
#include "LCD.h"

/******************************************Functions Prototypes******************************************/

// baudrate=9600 & F=16MHz
extern void UART0_Init(void); // initializing UART0 that is responsible of sending the data to PC (for debugging purposes)

extern unsigned char UART0_Available (void); // Check if FIFO of UART0 isn't full

extern void UART0_Write(char); // Sending the data (chars) to the PC (for debugging purposes)

extern void display_nearest_on_LCD(void); // displaying the nearest hall on the LCD

extern void UART2_Init(void); // initializing UART2 that is responsible for recieving the data from the GPS

extern unsigned char UART2_Available (void); // Check if FIFO of UART2 isn't empty

extern unsigned char UART2_Read(void); // Reading the data (chars) from the GPS module

#endif

