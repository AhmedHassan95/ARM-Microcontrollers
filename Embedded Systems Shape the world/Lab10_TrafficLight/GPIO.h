 /******************************************************************************
 *
 * [MODULE]: GPIO
 *
 * [FILE NAME]: GPIO.h
 *
 * [DESCRIPTION]: Header file for the GPIO Driver
 *
 * [AUTHOR]: Ahmed Hassan
 *
 *******************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include "tm4c123gh6pm.h"

/*******************************************************************************
 *                             Functions Prototypes                            *
 *******************************************************************************/
 
 /*******************************************************************************
 * [Function Name]: PortF_Init
 *
 * [Description]: Function to initialize PORTF Pins PF1, and PF3
 *
 * [Args]: None
 *
 * [in] None
 *
 * [out] None
 *
 * [in/out] None
 *
 * [Returns]: None
 *******************************************************************************/
void PortF_Init(void);

/*******************************************************************************
 * [Function Name]: PortE_Init
 *
 * [Description]: Function to initialize PORTE Pins PE0,PE1, and PE2
 *
 * [Args]: None
 *
 * [in] None
 *
 * [out] None
 *
 * [in/out] None
 *
 * [Returns]: None
 *******************************************************************************/
void PortE_Init(void);

/*******************************************************************************
 * [Function Name]: PortB_Init
 *
 * [Description]: Function to initialize PORTB PE0-5
 *
 * [Args]: None
 *
 * [in] None
 *
 * [out] None
 *
 * [in/out] None
 *
 * [Returns]: None
 *******************************************************************************/
void PortB_Init(void);

#endif /* GPIO_H_ */
