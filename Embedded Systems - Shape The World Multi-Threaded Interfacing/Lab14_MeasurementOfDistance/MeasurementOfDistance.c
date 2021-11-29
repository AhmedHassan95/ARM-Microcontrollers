// MeasurementOfDistance.c
// Runs on LM4F120/TM4C123
// Use SysTick interrupts to periodically initiate a software-
// triggered ADC conversion, convert the sample to a fixed-
// point decimal distance, and store the result in a mailbox.
// The foreground thread takes the result from the mailbox,
// converts the result to a string, and prints it to the
// Nokia5110 LCD.  The display is optional.
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

// Slide pot pin 3 connected to +3.3V
// Slide pot pin 2 connected to PE2(Ain1) and PD3
// Slide pot pin 1 connected to ground
//
//
// Solution Author: Ahmed Hassan
// Date: November 1, 2021

#include "tm4c123gh6pm.h"
#include "UART.h"
#include "ADC.h"
#include "SYSTICK.h"
#include "Nokia5110.h"
#include "LED.h"
#include "TExaS.h"

void EnableInterrupts(void);/* Enable interrupt */
unsigned char String[10]; 	/* Null-terminated ASCII string */
unsigned long Distance;   	/* Units 0.001 cm */
unsigned long ADCdata;    	/* 12-bit 0 to 4095 sample */
unsigned long Flag;       	/* 1 means valid Distance, 0 means Distance is empty */

// once the ADC and convert to distance functions are operational,
// you should use this main to build the final solution with interrupts and mailbox
int main(void)
{ 
	TExaS_Init(ADC0_AIN1_PIN_PE2, SSI0_Real_Nokia5110_Scope);
	
  /* Initialize ADC0, channel 1, sequencer 3 */
	/* Initialize Nokia5110 LCD (optional) */
	/* Initialize SysTick for 40 Hz interrupts */
	/* Initialize profiling on PF1 (optional) */
  /* Wait for clock to stabilize */
  ADC0_Init();    	
  Nokia5110_Init();   
  SysTick_Init(2000000);
	LED_Init();
	EnableInterrupts();

	/* Print a welcome message (optional) */
	Nokia5110_Clear();
	Nokia5110_SetCursor(0, 0);
	Nokia5110_OutString("Lab 14: ");
	Nokia5110_SetCursor(0, 1);
	Nokia5110_OutString("Measurement of Distance");
	Nokia5110_SetCursor(0, 5);
	Nokia5110_OutString("D = ");
	
   while(1)
	{ 
		/* Read mailbox */
		Flag = 0;
		
		if(Flag == 1)
		{
			Nokia5110_SetCursor(4, 5);
			UART_ConvertDistance(Distance);
			Nokia5110_OutString(String);    /* Output to Nokia5110 LCD (optional) */
		}		
  }
}


/*
// main1 is a simple main program allowing you to debug the ADC interface
int main1(void)
{ 
  TExaS_Init(ADC0_AIN1_PIN_PE2, SSI0_Real_Nokia5110_Scope);
  ADC0_Init();    // initialize ADC0, channel 1, sequencer 3
  EnableInterrupts();
  
	while(1)
	{ 
    ADCdata = ADC0_In();
  }
}
*/


/*
// main2, once the ADC is operational, you can use main2 to debug the convert to distance
int main2(void)
{ 
  TExaS_Init(ADC0_AIN1_PIN_PE2, SSI0_Real_Nokia5110_NoScope);
  ADC0_Init();    // initialize ADC0, channel 1, sequencer 3
  Nokia5110_Init();             // initialize Nokia5110 LCD
  EnableInterrupts();
	
  while(1)
	{ 
    ADCdata = ADC0_In();
    Nokia5110_SetCursor(0, 0);
    Distance = Convert(ADCdata);
    UART_ConvertDistance(Distance); // from Lab 11
    Nokia5110_OutString(String);    // output to Nokia5110 LCD (optional)
  }
}
*/
