/*
 * SYSTICK.c
 *  Author: Ahmed Mostafa Elhady
*/

#include "tm4c123gh6pm.h"  
#include "SYSTICK.h"

void systickInit(){
		NVIC_ST_CTRL_R=0;
		NVIC_ST_RELOAD_R=0xFFFFFF;
		NVIC_ST_CURRENT_R=0;
		NVIC_ST_CTRL_R=0x05;
}

void systick_wait_1ms(){
NVIC_ST_CTRL_R=0;
NVIC_ST_RELOAD_R = 16000 - 1;
NVIC_ST_CURRENT_R=0;
NVIC_ST_CTRL_R=0x05;
 while((NVIC_ST_CTRL_R & 0x00010000) == 0);
}

void delay_ms(int n)
{
 int i,j;
 for(i=0;i<n;i++)
 for(j=0;j<3180;j++)
 {}
}

void delay_us(int n)
{
 int i,j;
 for(i=0;i<n;i++)
	{
 for(j=0;j<3;j++)
 {}
 }
}
