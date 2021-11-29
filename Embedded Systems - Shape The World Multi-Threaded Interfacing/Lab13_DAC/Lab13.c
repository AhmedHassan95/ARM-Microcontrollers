// Lab13.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// edX Lab 13 
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// Port B bits 3-0 have the 4-bit DAC
// Port E bits 3-0 have 4 piano keys
//
// Solution Author: Ahmed Hassan
// Date: November 1, 2021

#include "tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"
#include "DAC.h"

/* Basic functions defined at end of startup.s */
void DisableInterrupts(void); /* Disable interrupts */
void EnableInterrupts(void);  /* Enable interrupts */
void delay(unsigned long msec); /* Delay in msec unit */

int main(void)
{ 
	unsigned char Pressed_Key;		/* Variable to store the current key state */
	unsigned char Previous_state;	/* Variable to store the previous key state */
	// Real Lab13 
	// for the real board grader to work 
	// you must connect PD3 to your DAC output

  TExaS_Init(SW_PIN_PE3210, DAC_PIN_PB3210,ScopeOn); // activate grader and set system clock to 80 MHz
	
	// PortE used for piano keys, PortB used for DAC        
  DAC_Init();	
	Sound_Init(); 
  Piano_Init();	
	EnableInterrupts();  /* Enable after all initialization are done */
	
  while(1)
	{                
		// input from keys to select tone
		// static testing, single step and record Vout 
		
		Pressed_Key = Piano_In(); 		/* Determine which key is pressed */
		
		if(Pressed_Key != Previous_state)
		{
			switch(Pressed_Key)
			{
				case 0: Sound_Off();							/* Turn off the Piano */			  
								break;	
				case 1: Sound_Tone(NOTE_C);      	/* Play C Hz wave */
								break;
				case 2: Sound_Tone(NOTE_D);      	/* Play D Hz wave	*/					
								break;
				case 4:	Sound_Tone(NOTE_E);      	/* Play E Hz wave */
								break;
				case 8: Sound_Tone(NOTE_G);      	/* Play G Hz wave */
								break;
				default: Sound_Off();    					/* Turn off the Piano */ 
								 break;
			}
			delay(10);
		}
		Previous_state = Pressed_Key;
	}
}

// Inputs: Number of msec to delay
// Outputs: None
void delay(unsigned long msec)
{ 
  unsigned long count;
	
  while(msec > 0 ) 
	{		// repeat while there are still delay
    count = 16000;    // about 1ms
    while (count > 0)
		{ 
      count--;
    } // This while loop takes approximately 3 cycles
    msec--;
  }
}
