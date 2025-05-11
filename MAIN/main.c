/*
 * main.c
 *  Author: Marium Waleed, Mai Mohamed, Menna Hassan
*/

#include "UART.h"
#include "SYSTICK.h"
#include "LCD.h"
#include "GPS.h"
#include "Buzzer.h"


int main()
{
	UART0_Init(); // Initializring UART0 (for debugging purposes)
	UART2_Init(); // Initializring UART2 to recieve data from the GPS module
	LCD_init();   // Initialzing the LCD
	buzzer_init(); // Initialzing the buzzer
	for(;;)
	{
	LCD_Command(clear_display); // Clearing the LCD
	GpsDataExtraction(); 				// Extracting the data recieved from the GPS module
	display_nearest_on_LCD(); 	// Displaying the name of the nearest hall on the LCD
	buzzer_update ();						// Updating the buzzer
	delay_ms(500);
		
	}	
}
