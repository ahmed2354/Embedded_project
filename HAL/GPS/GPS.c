/*
 * GPS.c
 *  Author: Ahmed Mahmoud Essam & Abobakr Ahmed Farouk
*/

#include "GPS.h"

char GPS_Data [100];
char GPS_logName[]="$GPRMC,";
char GPS_formatted[15][30];
char* token ;
static uint8_t check = 0;
long double CurrentLongitude;
long double CurrentLatitude;
long double Distances[6] = {0,0,0,0,0,0};		// an array that should be storing the distances between the current position and the positions of the halls
double HallsLongitudes[6] = {0.5459422757, 0.5459462462, 0.5459426672, 0.5459090575, 0.5458903792, 0.545911081}; //halls longitudes in rad
double HallsLatitudes[6] = {0.524718331, 0.5247101031, 0.5247367711, 0.5247058439, 0.5247276721, 0.5247436578};  //halls latitudes in rad

// Hall A, Hall C, Library, Credit Building, Gate 2,  Gate1 Locations

unsigned char current_nearest_index;


long double ToRad(double degree)		//to convert the latitude or the longitude recieved from the gps to rad (to understand more check the format of the longitudes/latitudes sent by the gps module frm here: https://community.particle.io/t/particle-and-gps-neo-6m-latitude-and-longitude-values/58649)
{
	unsigned short DegreeInt = (unsigned short) degree / 100;		// extracting the integer part and putting it in DegreeInt variable
	long double temp = degree - DegreeInt * 100;		// a temporary variable to extract the minutes part
	long double DegreeFraction = temp/60;						// dividing the minutes by 60 to get the fraction equivalent to it
	long double TotalDegree = DegreeInt + DegreeFraction;			// adding the integer part and the fraction part to get the whole angle in degree
	
	return TotalDegree * (PI / 180);				// converting the angle from degree to rad
}

long double CalcDistance(double longitude, double latitude)		// a function that calculates distance between the current position and the position of the halls
{
	long double a;
	long double c;
	long double CurrentLongitudeRad = ToRad(CurrentLongitude);	// converting the latitude and longitude of my current location to rad
	long double CurrentLatitudeRad = ToRad(CurrentLatitude);
	a = pow(sin((latitude - CurrentLatitudeRad)/2), 2) + cos(latitude) * cos(CurrentLatitudeRad) * pow(sin((longitude - CurrentLongitudeRad)/2), 2);
	c = 2 * atan2(sqrt(a), sqrt(1-a));
	return fabs(EarthRadius * c);
}	

char CompareLocations(){			// a function that compares the distances between me and the halls and returns a character corresponding to the hall that I am closer to
		unsigned char j;	
		unsigned char MinIndex=0;
		unsigned char i = 1;
	
	  for (j = 0; j <= 5; j++)
		{
			Distances[j] = CalcDistance(HallsLongitudes[j], HallsLatitudes[j]); 	// a loop that fills the Distances array which is declared in the header file and contains the distances between me and the halls
		}
		
		
    for (i=1;i<6;i++){
        if ((long double)(Distances[i] * 1000000000) < (long double)(Distances[MinIndex] * 1000000000))
            MinIndex = i;   //get index of the smallest distance
    }
		
		current_nearest_index = MinIndex;
    switch (MinIndex){		// a switch case that returns a character that is corresponding to the hall I am closer to
        case 0:
            return 'a';     //Hall A if index of the minimum distance is zero return char '0'
        case 1:
            return 'b';     //Hall C
        case 2:
            return 'c';     //Library
        case 3:
            return 'd';     //Credit Building
        case 4:
            return 'e';     //Gate 2
        case 5:
            return 'f';     //Gate 1
    }
}


void GpsDataExtraction() {
	
    unsigned char RecievedChar;
    unsigned char flag;
    unsigned char i;
    int j = 0;
			int k = 0;
    unsigned char fillGPScounter = 0;
		char* a;
		
		do
			{
				RecievedChar = UART2_Read();
				switch (RecievedChar)
							{
								case '$':
								check++;
								break;
								case 'G':
								check = check==1?2:0;
								break;
								case 'P':
								check = check==2?3:0;
								break;
								case 'R':
								check = check==3?4:0;
								break;
								case 'M':
								check = check==4?5:0;
								break;
								case 'C':
								check = check==5?6:0;
								break;
								case ',':
								if(check != 6) break;
								check=7;
								RecievedChar =  UART2_Read();
								
								//get values in GPMRC until *A
								while (RecievedChar != '*') {
								GPS_Data[fillGPScounter] = RecievedChar;
								RecievedChar =  UART2_Read();
								fillGPScounter++;
																	}
							}
			} while (check != 7);
		
	
			fillGPScounter = 0;
			token = strtok(GPS_Data, ",");	//cut until you find ","
			//walk through other tokens
			while (token != NULL) {
				strcpy(GPS_formatted[fillGPScounter], token);//copy what is in token into parseValue
				token = strtok(NULL, ",");
				fillGPScounter++;
			}
			
			CurrentLatitude = atof(GPS_formatted[2]);
			CurrentLongitude = atof(GPS_formatted[4]);
			
}


double nearest_distance (void) // for the operation of the buzzer
{
	return Distances[current_nearest_index];
}
