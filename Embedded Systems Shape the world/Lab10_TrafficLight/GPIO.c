 /******************************************************************************
 *
 * [MODULE]: GPIO
 *
 * [FILE NAME]: GPIO.c
 *
 * [DESCRIPTION]: Source file for the GPIO Driver
 *
 * [AUTHOR]: Ahmed Hassan
 *
 *******************************************************************************/

#include "GPIO.h"

/*******************************************************************************
 *                           Functions Definitions                             *
 *******************************************************************************/

/*******************************************************************************
 * [Function Name]: PortF_Init
 *
 * [Description]: 	Function to initialize PORTF Pins PF1, and PF3
 *
 * [Args]:					None
 *
 * [in]			  			None
 *
 * [out]		  			None
 *
 * [in/out]		 			None
 *
 * [Returns]:       None
 *******************************************************************************/
void PortF_Init(void)
{
  GPIO_PORTF_AMSEL_R &= ~0x0A;      /* 1) Disable analog on PF1 and PF3 */
  GPIO_PORTF_PCTL_R = 0x00000000;   /* 2) PCTL GPIO on PF1 and PF3 */
  GPIO_PORTF_DIR_R |= 0x0A;         /* 3) PF1 and PF3 are output pins */
  GPIO_PORTF_AFSEL_R &= ~0x0A;      /* 4) Disable alt funct on PF1 and PF3 */
  GPIO_PORTF_DEN_R |= 0x0A;         /* 5) Enable digital I/O on PF1 and PF3 */
}


/*******************************************************************************
 * [Function Name]: PortE_Init
 *
 * [Description]: 	Function to initialize PORTE Pins PE0,PE1, and PE2
 *
 * [Args]:					None
 *
 * [in]			  			None
 *
 * [out]		  			None
 *
 * [in/out]		 			None
 *
 * [Returns]:       None
 *******************************************************************************/
void PortE_Init(void)
{
  GPIO_PORTE_AMSEL_R &= ~0x07;      /* 1) Disable analog on PE2-0 */
  GPIO_PORTE_PCTL_R = 0x00000000;   /* 2) PCTL GPIO on PE2-0 */
  GPIO_PORTE_DIR_R &= ~0x07;        /* 3) PE0,PE1, andPE2 input pins */
  GPIO_PORTE_AFSEL_R &= ~0x07;      /* 4) Disable alt funct on PE2-0 */
  GPIO_PORTE_DEN_R |= 0x07;         /* 5) Enable digital I/O on PE0,PE1, and PE2 */
}

/*******************************************************************************
 * [Function Name]: PortB_Init
 *
 * [Description]: 	Function to initialize PORTB PE0-5
 *
 * [Args]:					None
 *
 * [in]			  			None
 *
 * [out]		  			None
 *
 * [in/out]		 			None
 *
 * [Returns]:       None
 *******************************************************************************/
void PortB_Init(void)
{
  GPIO_PORTB_AMSEL_R &= ~0x3F;      /* 1) Disable analog on PB5-0 */
  GPIO_PORTB_PCTL_R = 0x00000000;   /* 2) PCTL GPIO on PB5-0 */
  GPIO_PORTB_DIR_R |= 0x3F;         /* 3) PB5-0 pins are outputs */
  GPIO_PORTB_AFSEL_R &= ~0x3F;      /* 4) Disable alt funct on PB5-0 */
  GPIO_PORTB_DEN_R |= 0x3F;         /* 5) Enable digital I/O on PB5-0 */
}
