/*
 * LAUNCHPAD_IO.c
 *
 *  Created on: Mar 2, 2014
 *      Author: Nate
 */

#include "msp430g2553.h"

#define RED_LED	BIT0
#define GREEN_LED BIT6

#define LED_OUT	P1OUT
#define LED_SETUP P1DIR

/*
#define setupRLED() (LED_SETUP |= RED_LED)
#define RLED_ON	(LED_OUT |= RED_LED)
#define RLED_OFF (LED_OUT &=~RED_LED)
#define RLED_TOGGLE (LED_OUT ^=RED_LED)

#define setupGLED() (LED_SETUP |= RED_LED)
#define GLED_ON	(LED_OUT |= GREEN_LED)
#define GLED_OFF (LED_OUT &=~GREEN_LED)

*/

#define BUTTON	BIT3
#define setupButton() P1DIR &=~BUTTON; P1OUT |= BUTTON; P1REN |=  BUTTON
#define buttonPressed ((BUTTON & P1IN)==0x0)


