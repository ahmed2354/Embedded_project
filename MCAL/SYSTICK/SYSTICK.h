/*
 * SYSTICK.h
 *  Author: Ahmed Mostafa Elhady
*/

#ifndef SYSTICK_H
#define SYSTICK_H

/******************************************Definitions******************************************/

#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))

/******************************************Functions Prototypes******************************************/

extern void systickInit(); //Systick initialization
extern void systick_wait_1ms();  //wait 1 msec
extern void delay_ms(int n); /* mili second delay function */
extern void delay_us(int n); /* micro second delay function */


 #endif
