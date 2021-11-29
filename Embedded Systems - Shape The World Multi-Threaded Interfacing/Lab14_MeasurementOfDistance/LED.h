#ifndef LED_H
#define LED_H

#include "tm4c123gh6pm.h"  

// Intialize the LED on PORTF Pin 1
// Input: None
// Output: None
void LED_Init(void);

// Function to toggle the LED on PORTF pin 1
void LED_Toggle(void);

#endif
