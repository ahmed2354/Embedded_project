/*
 * Buzzer.c
 *  Author: Marium Waleed
*/

#include "Buzzer.h"

void buzzer_init(void)
{
	SYSCTL_RCGCGPIO_R |= (1 << PORTD);
	while ((SYSCTL_PRGPIO_R & (1 << PORTD)) == 0);
	GPIO_PORTD_DIR_R |= (1<<buz_pin);					 // Configuring as output
	GPIO_PORTD_DEN_R |= (1<<buz_pin);					 // Enabling didtal operation for the pin
	GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;         // Unlock Port D
  GPIO_PORTD_CR_R |= (1<<buz_pin);
  GPIO_PORTD_AMSEL_R &= ~(1<<buz_pin);       // Disable analog
	GPIO_PORTD_PCTL_R &= ~0x0000F000;          // Configure as GPIO
  GPIO_PORTD_AFSEL_R &= ~(1<<buz_pin);       // Disable alternate function

}

/* Enabling the buzzer to start buzzing if the distance between the current location and any of the halls is less than (small distance) 25 meters */
void buzzer_update (void) 
{
	if(nearest_distance() <= small_distance)
	{
		GPIO_PORTD_DATA_R |= (1<<buz_pin);
	}
	else
	{
		GPIO_PORTD_DATA_R &= ~(1<<buz_pin);
	}
	
}
