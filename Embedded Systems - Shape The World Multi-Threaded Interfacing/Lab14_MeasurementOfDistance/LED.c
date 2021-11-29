#include "LED.h"

// Intialize the LED on PORTF Pin 1
// Input: None
// Output: None
void LED_Init(void)
{ 
  volatile unsigned long delay;
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF; 		/* 1) Activate clock for Port F */
  delay = SYSCTL_RCGC2_R;         			/* allow time for clock to stabilize */
  GPIO_PORTF_DIR_R |= 0x02;      			/* 2) Make PF2 output */
  GPIO_PORTF_AFSEL_R &= ~0x02;     			/* 3) Disable alternate function on PF2 */
  GPIO_PORTF_DEN_R |= 0x02;      			/* 4) Enable digital I/O on PF2 */
  GPIO_PORTF_AMSEL_R &= ~0x02;     			/* 5) Disable analog function on PF2 */
  GPIO_PORTF_DATA_R &= ~0x02;     			/* 6) Turn off LED at the beginning */
}

// Function to toggle the LED on PORTF pin 1
void LED_Toggle(void)
{ 
	GPIO_PORTF_DATA_R ^= 0x02;
}
