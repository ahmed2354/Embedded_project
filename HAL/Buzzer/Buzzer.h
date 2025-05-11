/*
 * Buzzer.h
 *  Author: Marium Waleed
*/

#ifndef _BUZZER_H_
#define _BUZZZER_H_

//connected on port D pin 3

#include "GPS.h"
#include "tm4c123gh6pm.h"

/******************************************Definitions******************************************/

#define GPIO_LOCK_KEY          0x4C4F434B
#define PORTD 3
#define buz_pin 3  //choose a pin 
#define small_distance  25 //around 25 meters

/******************************************Functions Prototypes******************************************/

extern void buzzer_init(void); // Initializing the buzzer
extern void buzzer_update (void); // Updating the data sent to the buzzer and its status

#endif
