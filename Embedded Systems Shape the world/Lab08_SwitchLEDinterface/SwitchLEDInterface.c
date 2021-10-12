// ***** 0. Documentation Section *****
// SwitchLEDInterface.c for Lab 8
// Runs on LM4F120/TM4C123
// Use simple programming structures in C to toggle an LED
// while a button is pressed and turn the LED on when the
// button is released.  This lab requires external hardware
// to be wired to the LaunchPad using the prototyping board.
// January 15, 2016
//      Jon Valvano and Ramesh Yerraballi
// Solution Author: Ahmed Hassan
// Date: September 10,2021


// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"  

// ***** 2. Global Declarations Section *****

// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); /* Disable interrupts */
void EnableInterrupts(void);  /* Enable interrupts */
void SW_Init(void);	/* Switch Initalization */
void LED_Init(void);	/* LED Initalization */
void Delay_1ms(unsigned long time);	/* Delay Function */

// ***** 3. Subroutines Section *****

// PE0, PB0, or PA2 connected to positive logic momentary switch using 10k ohm pull down resistor
// PE1, PB1, or PA3 connected to positive logic LED through 470 ohm current limiting resistor
// To avoid damaging your hardware, ensure that your circuits match the schematic
// shown in Lab8_artist.sch (PCB Artist schematic file) or 
// Lab8_artist.pdf (compatible with many various readers like Adobe Acrobat).
int main(void)
{ 
	//**********************************************************************
	// The following version tests input on PE0 and output on PE1
	//**********************************************************************
	volatile unsigned long delay = 0;	/* Local variable to store the Delay Function */
	TExaS_Init(SW_PIN_PE0, LED_PIN_PE1, ScopeOn);  /* Activate grader and set system clock to 80 MHz */
  
	SYSCTL_RCGC2_R |= 0x00000010;
	delay = SYSCTL_RCGC2_R;	
	
	SW_Init();	/* Switch Initialization */
	LED_Init();	/* LED Initialization */
  	EnableInterrupts();	/* Enable interrupts for the grader */
	
	
	while(1)
	{
		if(GPIO_PORTE_DATA_R & (1<<0))
		{
			GPIO_PORTE_DATA_R ^= (1<<1);	/* Toggle LED */
			Delay_1ms(100);	/* Delay 100 ms */
		}
		else
		{
			GPIO_PORTE_DATA_R |= (1<<1);	/* Turn ON LED */
		}
	}
}


/* Switch Initialization Subroutine */
void SW_Init(void)
{
	GPIO_PORTE_AMSEL_R &= ~(1<<0); /* Disable the Analog on PE0 */
	GPIO_PORTE_AFSEL_R &= ~(1<<0);	/* Disable the Alt. funct on PE0 */
	GPIO_PORTE_PCTL_R &= 0xFFFFFFF0;	/* Clear PCTL on PE0 */
	GPIO_PORTE_DIR_R &= ~(1<<0);	/* Configure PE0 as Input Pin */
	GPIO_PORTE_DEN_R |= (1<<0);	/* Enable digital Pin on PE0 */
}

/* LED Initialization Subroutine */
void LED_Init(void)
{
	GPIO_PORTE_AMSEL_R &= ~(1<<1); /* Disable the Analog on PE1 */
	GPIO_PORTE_AFSEL_R &= ~(1<<1);	/* Disable the Alt funct on PE1 */
	GPIO_PORTE_PCTL_R &= 0xFFFFFF0F;	/* Clear PCTL on PE1 */
	GPIO_PORTE_DIR_R |= (1<<1);	/* Configure PE1 as Output Pin */
	GPIO_PORTE_DEN_R |= (1<<1);	/* Enable digital Pin on PE1 */
	GPIO_PORTE_DATA_R |= (1<<1);	/* Turn On LED at the beginning */
	Delay_1ms(100);	/* Delay 1ms */
}

/* Delay Subroutine */
void Delay_1ms(unsigned long time)
{
	unsigned long count;
		
	while(time > 0)
	{
		count = 16000;
		while(count > 0)
		{
			count--;
		}
		time--;
	}
}
