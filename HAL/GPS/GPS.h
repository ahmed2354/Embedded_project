#ifndef _GPS_H_
#define _GPS_H_

#include <math.h>
#include <string.h>
#include "UART.h"
#include <stdlib.h>
#define EarthRadius 6371000
#define PI 3.14159265359
//#define MinDistance 10   

//extern void PPS_PE2_Init();
extern long double ToRad(double degree);


extern void GpsDataExtraction(void); // to operate on the global string recieved from the UART

extern long double CalcDistance(double longitute, double latitude); // that function should return the distance between my current posistion and each hall (hall locations should be passed by the function parameters)

extern char CompareLocations(void); 	// a function that compares the distances between me and the halls and returns a character corresponding to the hall that I am closer to

extern void GPS_FORMAT(void);
#endif
