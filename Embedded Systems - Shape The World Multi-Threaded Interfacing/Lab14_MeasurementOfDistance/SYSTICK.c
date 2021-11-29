#include "SYSTICK.h"

// Initialize SysTick interrupts to trigger at 40 Hz, 25 ms
void SysTick_Init(unsigned long period)
{
 NVIC_ST_CTRL_R = 0;		// Disable SysTick during setup
 NVIC_ST_CURRENT_R = 0; // Any write to current clears it
 NVIC_ST_RELOAD_R = period-1 ; 
 NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x20000000; // Priority 1
 NVIC_ST_CTRL_R = 0x007; 	// Enable SysTick with core clock and interrupts
}

// executes every 25 ms, collects a sample, converts and stores in mailbox
void SysTick_Handler(void)
{ 
	LED_Toggle();	/* Toggle the LED on PF1 */
	LED_Toggle();	/* Toggle the LED on PF1 */ 
	ADCdata = ADC0_In();	/* Read the digital data */
	Distance = Convert(ADCdata);	/* Convert the data to be in the form 0.0001 cm */
	Flag = 1;	/* Raise the flag to indicate that there is a data */
	LED_Toggle();	/* Toggle the LED on PF1 */
}
