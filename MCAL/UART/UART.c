/*
 * UART.c
 *  Author: Marium Waleed, Mai Mohamed, Menna Hassan
*/

#include "UART.h"

void UART0_Init(void)
{
    // should be called only once
    SYSCTL_RCGCUART_R |= 0x00000001; // activate UART0
    SYSCTL_RCGCGPIO_R |= 0x00000001; // activate port A
    UART0_CTL_R &= ~0x00000001; // disable UART
    UART0_IBRD_R = 104; 
    UART0_FBRD_R = 11; 
    UART0_LCRH_R = 0x00000070; // 8 bit, no parity bits, one stop, FIFOS
    UART0_CTL_R |= 0x00000301; // enable UART, TXE, RXE
    GPIO_PORTA_AFSEL_R |= 0x03; // enable alt funct on PA1-0
    GPIO_PORTA_DEN_R |= 0x03; // configure PA1-0 as UART0
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011;
    GPIO_PORTA_AMSEL_R &= ~0x03; // disable analog on PA1-0
}


/*-------------------------------------------*/
// initialize UART2 to recieve data from GPS	
// baudrate=9600 & F=16MHz

void UART2_Init(void)
{
    // should be called only once
    SYSCTL_RCGCUART_R |= 0x00000004; // activate UART2
    SYSCTL_RCGCGPIO_R |= 0x00000008; // activate port D
	GPIO_PORTD_LOCK_R     =     GPIO_LOCK_KEY;
    UART2_CTL_R &= ~0x00000001; // disable UART
    UART2_IBRD_R = 104; 
    UART2_FBRD_R = 11; 
    UART2_LCRH_R = 0x00000070; // 8 bit, no parity bits, one stop, FIFOS
    UART2_CTL_R |= 0x00000301; // enable UART, TXE, RXE
    GPIO_PORTD_AFSEL_R |= 0xC0; // enable alt funct on PA1-0
    GPIO_PORTD_DEN_R |= 0xC0; // configure PA1-0 as UART0
    GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0x00FFFFFF) + 0x11000000;
    GPIO_PORTD_AMSEL_R &= ~0xC0; // disable analog on PA1-0
}


/*-------------------------------------------*/

// Check if FIFO of UART0 isn't full
unsigned char UART0_Available (void) 
{
		if((UART0_FR_R&0X0020)==0) //(FIFO FULL FLAG=ZER0)==>EMPTY==>Can Transmit Data To Reg.
		{
			return 1;
		}
		return 0;
}

unsigned char UART2_Available (void) 
{
		if((UART2_FR_R&0X0020)==0) //(FIFO FULL FLAG=ZER0)==>EMPTY==>Can Transmit Data To Reg.
		{
			return 1;
		}
		return 0;
}
/*-------------------------------------------*/
// write data to data register of UART0
// transmit data to PC
void UART0_Write(char display)
{
    while (UART0_Available() == 0); // check if the buffer is full, when there is space send
    UART0_DR_R = display; 
}
/*-------------------------------------------*/

// Recieve data from the GPS on UART2
unsigned char UART2_Read(void)
{
	while ((UART2_FR_R & UART_FR_RXFE) != 0); 
					return ((unsigned char) UART2_DR_R & UART_DR_DATA_M);
}

// A function that takes the index of the smallest distance and prints the closest Hall on the LCD screen
void display_nearest_on_LCD(void)
{
	char nearest =0;
	nearest = CompareLocations();
	
	switch(nearest)
	{
		case 'a':
			LCD_String("Hall A");
			break;
		case 'b':
			LCD_String("Hall C");
			break;
		case 'c':
			LCD_String("Library");
			break;
		case 'd':
			LCD_String("Credit Building");
			break;
		case 'e':
			LCD_String("Gate 2");
			break;
		case 'f':
			LCD_String("Gate 1");
			break;
	}
}
