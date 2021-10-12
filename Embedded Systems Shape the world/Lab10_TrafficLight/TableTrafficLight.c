// ***** 0. Documentation Section *****
// TableTrafficLight.c for Lab 10
// Runs on LM4F120/TM4C123
// Index implementation of a Moore finite state machine to operate a traffic light.  
// Daniel Valvano, Jonathan Valvano
// January 15, 2016
//
// Solution Author: Ahmed Hassan
// Date: September 10,2021

// east/west red light connected to PB5
// east/west yellow light connected to PB4
// east/west green light connected to PB3
// north/south facing red light connected to PB2
// north/south facing yellow light connected to PB1
// north/south facing green light connected to PB0
// pedestrian detector connected to PE2 (1=pedestrian present)
// north/south car detector connected to PE1 (1=car present)
// east/west car detector connected to PE0 (1=car present)
// "walk" light connected to PF3 (built-in green LED)
// "don't walk" light connected to PF1 (built-in red LED)

/* ***** 1. Pre-processor Directives Section ***** */
#include "TExaS.h"
#include "tm4c123gh6pm.h"
#include "PLL.h"
#include "SysTick.h"
#include "GPIO.h"

#define GoWest     0	/* Turn on Green Led in West/East way and Red Leds in others */
#define WaitWest   1	/* Turn on Yellow Led in West/East way and Red Leds in others */
#define GoSouth    2	/* Turn on Green Led in South/North way and Red Leds in others */
#define WaitSouth  3	/* Turn on Yellow Led in South/North way and Red Leds in others */
#define Walk   		 4	/* Turn on Green Led in Pedestrian way and Red Leds in others */
#define HurryUP1   5	/* Turn on Red Led in Pedestrian way "First Flash" */
#define HurryUP2   6	/* Turn Off Red Led in Pedestrian way "First Flash" */
#define HurryUP3   7	/* Turn on Red Led in Pedestrian way "Second Flash" */
#define HurryUP4   8	/* Turn Off Red Led in Pedestrian way "Second Flash" */
#define HurryUP5   9	/* Turn on Red Led in Pedestrian way "Third Flash" */

#define OFF			0x00
#define RED  		   	0x02
#define GREEN   	 	0x08
#define LIGHTS		 	GPIO_PORTB_DATA_R
#define PEDESTRIAN_LIGHTS     	GPIO_PORTF_DATA_R
#define SENSORS			GPIO_PORTE_DATA_R

/* ***** 2. Global Declarations Section ***** */

/* FUNCTION PROTOTYPES: Each subroutine defined */
void DisableInterrupts(void); /* Disable interrupts */
void EnableInterrupts(void);  /* Enable interrupts */

/* Linked data structure */
struct State
{
  unsigned long Out;		/* 6 Pattern to output */
  unsigned long WalkLed;	/* Pedestrians Leds */
  unsigned long Time;		/* Delay in 10ms units */
  unsigned long Next[8];	/* Next States for inputs 0,1,2,3,4,5,6,7 */  
}; 

typedef const struct State SType;

SType FSM[10]=
{
 {0x0C, RED, 200, {GoWest, GoWest, WaitWest, WaitWest, WaitWest, WaitWest, WaitWest, WaitWest}},
 {0x14, RED, 100, {GoWest, GoWest, GoSouth, GoSouth, Walk, Walk, GoSouth, GoSouth}},
 {0x21, RED, 200, {GoSouth, WaitSouth, GoSouth, WaitSouth, WaitSouth, WaitSouth, WaitSouth, WaitSouth}},
 {0x22, RED, 100, {GoSouth, GoWest, GoSouth, GoWest, Walk, Walk, Walk, Walk}},
 {0x24, GREEN, 200, {Walk, HurryUP1, HurryUP1, HurryUP1, Walk, HurryUP1, HurryUP1, HurryUP1}},
 {0x24, RED, 100, {HurryUP2, HurryUP2, HurryUP2, HurryUP2, HurryUP2, HurryUP2, HurryUP2, HurryUP2}},
 {0x24, OFF, 100, {HurryUP3, HurryUP3, HurryUP3, HurryUP3, HurryUP3, HurryUP3, HurryUP3, HurryUP3}},
 {0x24, RED, 100, {HurryUP4, HurryUP4, HurryUP4, HurryUP4, HurryUP4, HurryUP4, HurryUP4, HurryUP4}},
 {0x24, OFF, 100, {HurryUP5, HurryUP5, HurryUP5, HurryUP5, HurryUP5, HurryUP5, HurryUP5, HurryUP5}},
 {0x24, RED, 100, {Walk, GoWest, GoSouth, GoWest, Walk, GoWest, GoSouth, GoWest}}
};

unsigned long S;  /* Index to the current state */
unsigned long Input; /* Local variable to store input from sensors in it */

/* ***** 3. Subroutines Section ***** */

int main(void)
{ 
  volatile unsigned long delay;
  TExaS_Init(SW_PIN_PE210, LED_PIN_PB543210,ScopeOff); /* Activate grader and set system clock to 80 MHz */	
  EnableInterrupts();
	
  SYSCTL_RCGC2_R |= 0x00000032;     /* Activate clock for PORTF, PORTB, and PORTE */
  delay = SYSCTL_RCGC2_R;           /* Allow time for clock to start */
	
  PLL_Init();     	/* PLL Initialization 80 MHz */
  SysTick_Init();  	/* SysTick Initialization */
  PortB_Init();		/* PORTB Initialization */
  PortE_Init();		/* PORTE Initialization */
  PortF_Init();		/* PORTF Initialization */

  S = GoWest;	/* Initial State */
	
  while(1)
  {
    LIGHTS = FSM[S].Out;  			/* Set lights */
    PEDESTRIAN_LIGHTS  = FSM[S].WalkLed;  	/* Set lights */
    SysTick_Wait10ms(FSM[S].Time);		/* Delay in ms units */
    Input = (SENSORS & 0x07);    		/* Read sensors */
    S = FSM[S].Next[Input];   			/* Update the current state */
  }
}

