// TuningFork.c Lab 12
// Runs on LM4F120/TM4C123
// Use SysTick interrupts to create a squarewave at 440Hz.  
// There is a positive logic switch connected to PA3, PB3, or PE3.
// There is an output on PA2, PB2, or PE2. The output is 
//   connected to headphones through a 1k resistor.
// The volume-limiting resistor can be any value from 680 to 2000 ohms
// The tone is initially off, when the switch goes from
// not touched to touched, the tone toggles on/off.
//                   |---------|               |---------|     
// Switch   ---------|         |---------------|         |------
//
//                    |-| |-| |-| |-| |-| |-| |-|
// Tone     ----------| |-| |-| |-| |-| |-| |-| |---------------
//
// Daniel Valvano, Jonathan Valvano
// January 15, 2016

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2015

 Copyright 2016 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// Solution Author: Ahmed Hassan
// Date: November 1, 2021

#include "TExaS.h"
#include "tm4c123gh6pm.h"

/* Basic functions defined at end of startup.s */
void DisableInterrupts(void); /* Disable interrupts */
void EnableInterrupts(void);  /* Enable interrupts */
void WaitForInterrupt(void);  /* Low power mode */

volatile unsigned long time = 0;
volatile unsigned long Prev_state = 0;
volatile unsigned long flag = 0;

/* Input from PA3, output from PA2 */
void Sound_Init(void)
{ 
  unsigned long volatile delay;	
  SYSCTL_RCGC2_R |= 0x00000001; 		// Activate clock for port A
  delay = SYSCTL_RCGC2_R;  
  time = 90909;               	  		// 880 Hz
  GPIO_PORTA_AMSEL_R &= ~0x0C;      		// Disable analog functionality on PA3, PA2
  GPIO_PORTA_PCTL_R &= ~0x0000FF00; 		// Configure PA3, PA2 as GPIO
  GPIO_PORTA_DIR_R = 0x04;     			// Make PA2 output, and PA3 input
  GPIO_PORTA_DR8R_R |= 0x04;    		// Enable 8 mA drive on PA2
  GPIO_PORTA_AFSEL_R &= ~0x0C;  		// Disable alt funct on PA3, PA2
  GPIO_PORTA_PDR_R = 0x08;  			// Activate the Pull down resistor for PA3
  GPIO_PORTA_DEN_R |= 0x0C;     		// Enable digital I/O on PA3, PA2
  GPIO_PORTA_DATA_R &= ~0x0C;   		// Make PA2 low
}

/* SysTick timer Initialization */
void Systick_Init(void)
{ 
  NVIC_ST_CTRL_R = 0;           		// Disable SysTick during setup
  NVIC_ST_RELOAD_R = time-1;       		// Reload value for 880 Hz
  NVIC_ST_CURRENT_R = 0;        		// Any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF); // priority 0
  NVIC_ST_CTRL_R = 0x00000007;  		// Enable with core clock and interrupts
}

/* Called at 880 Hz */
void SysTick_Handler(void)
{
	if( (GPIO_PORTA_DATA_R & 0x08) && (Prev_state == 0) )
	{
		if(flag == 0)
		{
			GPIO_PORTA_DATA_R ^= 0x04;	/* Toggle PA2 */
			flag = 1;	/* Rise the flag */
		}
		else
		{
			GPIO_PORTA_DATA_R &= ~0x04;	/* Clear PA2 */
			flag = 0; /* Reset the flag */
		}
	}
	else 
	{
		if(flag == 1)
		{
			GPIO_PORTA_DATA_R ^= 0x04;	/* Toggle PA2 */
		}
		else
		{
			GPIO_PORTA_DATA_R &= ~0x04;	/* Clear PA2 */
		}
	}
	
	Prev_state = (GPIO_PORTA_DATA_R & 0x08) >> 3;	/* Update the previous state */
}

int main(void)
{
   /* Activate grader and set system clock to 80 MHz */
  TExaS_Init(SW_PIN_PA3, HEADPHONE_PIN_PA2,ScopeOn); 
  Sound_Init();         
  Systick_Init();
  EnableInterrupts();   /* Enable after all initialization are done */
  
  while(1)
  {
    /* Main program is free to perform other tasks */
    /* Do not use WaitForInterrupt() here, it may cause the TExaS to crash */
  }
}
