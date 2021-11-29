// DAC.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Implementation of the 4-bit digital to analog converter
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// Port B bits 3-0 have the 4-bit DAC

#include "DAC.h"
#include "tm4c123gh6pm.h"

// **************DAC_Init*********************
// Initialize 4-bit DAC 
// Input: none
// Output: none
void DAC_Init(void)
{
	volatile unsigned long delay;
	
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;	/* 1) Activate clock on PORTB */
  delay = SYSCTL_RCGC2_R;              	/* delay */  
  GPIO_PORTB_AMSEL_R &= ~0x0F;         	/* 2) Disable analog function */
  GPIO_PORTB_PCTL_R &= ~0x0000FFFF;   	/* 3) GPIO clear bit PCTL */  
  GPIO_PORTB_DIR_R |= 0x0F;         		/* 4) PB3 -- PB0 output */   
	GPIO_PORTB_DR8R_R |= 0x0F;          	/* 5) Enable 8 mA drive on PB3 - PB0 */
  GPIO_PORTB_AFSEL_R &= ~0x0F;         	/* 6) No alternate function */
	GPIO_PORTB_DEN_R |= 0x0F;          		/* 7) Enable digital pins PB3-PB0 */       
	GPIO_PORTB_DATA_R &= ~0x0F;         	/* 8) Initialize DAC to off */
}


// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
void DAC_Out(unsigned long data)
{
  GPIO_PORTB_DATA_R = data;
}
