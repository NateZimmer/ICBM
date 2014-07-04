/*
 * RGB.h
 *
 *  Created on: Jan 28, 2014
 *      Author: Nate
 */

#ifndef RGB_H_
#define RGV_H_

#include "msp430g2553.h"

#define GLED	BIT6
#define BLED	BIT5
#define RLED	BIT5

#define GLED_SETUP	P3DIR |=GLED
#define GLED_DSETUP	P3DIR &=~GLED
#define GLED_OUT	P3OUT
#define GLED_ON		GLED_OUT &=~GLED
#define GLED_OFF	GLED_OUT |=GLED
#define GLED_NOT	GLED_OUT ^=GLED
#define GLED_A_OFF	GLED_SETUP; GLED_OFF; P3SEL &=~GLED
#define GLED_A_ON	GLED_SETUP; GLED_ON; P3SEL |=GLED

#define BLED_SETUP	P3DIR |=BLED
#define BLED_DSETUP	P3DIR &=~BLED
#define BLED_ON		P3OUT &=~BLED
#define BLED_OFF	P3OUT |=BLED
#define BLED_NOT	P3OUT ^=BLED
#define BLED_A_OFF	BLED_SETUP; BLED_OFF; P3SEL &=~BLED
#define BLED_A_ON	BLED_SETUP; BLED_ON; P3SEL |=BLED

#define	RLED_SETUP	P2DIR |=RLED
#define RLED_DSETUP	P2DIR &=~RLED
#define RLED_OUT	P2OUT
#define RLED_ON		P2OUT &=~RLED
#define RLED_OFF	P2OUT |=RLED
#define RLED_NOT	P2OUT ^=RLED
#define RLED_A_OFF	RLED_SETUP; RLED_OFF; P2SEL &=~RLED
#define RLED_A_ON	RLED_SETUP; RLED_ON; P2SEL |=RLED

void setupRGB();
void fadeRgb();
void rgbOff();
void rgbOn();

#endif /* LED_FADE_H_ */
