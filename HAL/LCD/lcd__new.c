/*
 * LCD.c
 *  Author: Omar Mohamed Eid
*/

#include "LCD.h"


/* LCD and GPIOB initialization Function */ 
void LCD_init(void)
{
 SYSCTL_RCGCGPIO_R |= (1 << PORTB); /* Enable Clock to GPIOB*/
	while ((SYSCTL_PRGPIO_R & (1 << PORTB)) == 0);
 GPIO_PORTB_DEN_R |= 0xFF;
	
 GPIO_PORTB_DIR_R |= 0xFF; /* Declare GPIOB pins as digital pins */
	
 LCD_Command(Normal_Font_Size);
 LCD_Command(Four_Bit_Mode);
 LCD_Command(CursorRight);
 LCD_Command(clear_display);
 LCD_Command(Blink);
 
}

void LCD_Command(unsigned char command)
{
    LCD_Control(command & 0xF0, 0);   /* Write the upper half of the control and data bits to LCD */
    LCD_Control(command << 4, 0);     /* Write the lower half of the control and data bits to LCD */
    
	// to satisfy the delays of the enable pulse listed in the data sheet of the LCD commands
    if (command < 4)
        delay_ms(2);         /* 2ms delay for commands 1 and 2 */
    else
        delay_us(40);        /* 40us delay for other commands */
}


void LCD_Control(unsigned char data, unsigned char control)
{

    data &= 0xF0;       /* Extract upper half of the control and data bits for data */
    control &= 0x0F;    /* Extract lower half of the control and data bits for control */
    GPIO_PORTB_DATA_R = data | control;       /* Set RS and R/W to zero for write operation */
		GPIO_PORTB_DATA_R = data | control;
    GPIO_PORTB_DATA_R = data | control | EN;  /* Provide Pulse to Enable pin to perform wite operation */
    GPIO_PORTB_DATA_R = data; /*Send data */
    GPIO_PORTB_DATA_R = 0; /* stop writing data to LCD */
}


void LCD_Char(unsigned char data)
{
    LCD_Control(data & 0xF0, RS);    /* Write upper half of the control and data bits to LCD and RS = 1 to write data */
    LCD_Control(data << 4, RS);      /* Write lower half of the control and data bits to LCD and RS = 1 to write data */
    delay_us(40);
}


void LCD_String (char *str)	/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)  /* Send each char of string till the NULL */
	{
		LCD_Char(str[i]);  /* Call LCD data write */
	}
}

