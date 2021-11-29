#ifndef SYSTIC_H_
#define SYSTIC_H_

#include "tm4c123gh6pm.h"
#include "LED.h"
#include "ADC.h"
#include "UART.h"

extern unsigned char String[10]; /* Null-terminated ASCII string */
extern unsigned long Distance;   /* Units 0.001 cm */
extern unsigned long ADCdata;    /* 12-bit 0 to 4095 sample */
extern unsigned long Flag;       /* 1 means valid Distance, 0 means Distance is empty */


// Initialize SysTick interrupts to trigger at 40 Hz, 25 ms
void SysTick_Init(unsigned long period);

#endif
