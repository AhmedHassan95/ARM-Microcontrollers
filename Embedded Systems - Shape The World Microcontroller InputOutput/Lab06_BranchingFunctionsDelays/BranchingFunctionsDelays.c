// BranchingFunctionsDelays.c Lab 6
// Runs on LM4F120/TM4C123
// Use simple programming structures in C to 
// toggle an LED while a button is pressed and 
// turn the LED on when the button is released.  
// This lab will use the hardware already built into the LaunchPad.
// Daniel Valvano, Jonathan Valvano
// January 15, 2016
// Solution Author: Ahmed Hassan
// Date: September 10,2021

// built-in connection: PF0 connected to negative logic momentary switch, SW2
// built-in connection: PF1 connected to red LED
// built-in connection: PF2 connected to blue LED
// built-in connection: PF3 connected to green LED
// built-in connection: PF4 connected to negative logic momentary switch, SW1

#include "TExaS.h"

#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOF      0x00000020  /* PORTF Clock Gating Control */

/* Basic functions defined at end of startup.s */
void DisableInterrupts(void); /* Function to Disable Interrupts */
void EnableInterrupts(void);  /* Function to Enable Interrupts */
void PortF_Init(void);				/* Function to Initialize PORTF */
void Delay_100ms(unsigned long time);	/* Function to count Delay in ms units */

int main(void)
{
  /* Initialization goes here */
  unsigned long volatile delay;
  TExaS_Init(SW_PIN_PF4, LED_PIN_PF2);  /* Activate grader and set system clock to 80 MHz */
  EnableInterrupts();      		/* Enable interrupts for the grader */
  PortF_Init();				/* PORTF Initialization */
	
  GPIO_PORTF_DATA_R |= 0x04; 		/* Turn On LED at the beginning */
	
  while(1)
  {
    /* Body goes here */
	  Delay_100ms(1);
	  
	if(! (GPIO_PORTF_DATA_R & (1<<4)) )
	{
		GPIO_PORTF_DATA_R ^= (1<<2);	/* Toggle LED */
	}
	else
	{
		/* Do Nothing */
	}
  }
}


void PortF_Init(void)
{
	volatile unsigned long delay;	/* Local varaible delay used to miss some clock cycles */
	
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;	/* Enable the clock of PORTF */
	delay = SYSCTL_RCGC2_R;	/* Allow time for clock to start */
	GPIO_PORTF_AMSEL_R &= ~0x14;	/* Disable Analog for PF2 and PF4 */
	GPIO_PORTF_AFSEL_R &= ~0x14;	/* Disable Alt. function for PF2 and PF4 */
	GPIO_PORTF_PCTL_R &= ~0x000F0F00;	/* PCTL GPIO on PF2 and PF4 */
	GPIO_PORTF_PUR_R |= 0x10;	/* Enable the PULL-Up on PF4 */
	GPIO_PORTF_DIR_R = 0x04;	/* Configure PF2 as Output and PF4 as Input */
	GPIO_PORTF_DEN_R |= 0x14;	/* Digital Enable on PF2 and PF2 */
}

void Delay_100ms(unsigned long time)
{
	unsigned long i;
	
	while(time > 0)
	{
		i = 1333333;
		
		while(i > 0)
		{
			i = i-1;
		}
		time = time-1;
	}
}
