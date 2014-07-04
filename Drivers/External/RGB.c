/*
 * led_fade.c
 *
 *  Created on: Jan 28, 2014
 *      Author: Nate
 */

#include "RGB.h"


static int gseq = 33;
static int rseq = 66;
static int bseq = 0;

/*
const int led_dutys2[] = { 1002, 1002, 1002, 1002, 1001, 1001, 1000, 998, 997,
		994, 992, 989, 985, 981, 975, 970, 963, 956, 948, 938, 928, 917, 905,
		892, 877, 862, 845, 827, 807, 786, 764, 740, 715, 688, 659, 629, 597,
		564, 528, 490, 451, 410, 366, 321, 273, 224, 172, 118, 61, 2, 2, 61,
		118, 172, 224, 273, 321, 366, 410, 451, 490, 528, 564, 597, 629, 659,
		688, 715, 740, 764, 786, 807, 827, 845, 862, 877, 892, 905, 917, 928,
		938, 948, 956, 963, 970, 975, 981, 985, 989, 992, 994, 997, 998, 1000,
		1001, 1001, 1002, 1002, 1002, 1002,

};
*/

const int led_dutys2[] = { 1002, 1002, 1002, 1002, 1001, 1001, 1000, 998, 997,
		994, 992, 989, 985, 981, 975, 970, 963, 956, 948, 938, 928, 917, 905,
		892, 877, 862, 845, 827, 807, 786, 764, 740, 715, 688, 659, 629, 597,
		564, 528, 490, 451, 410, 366, 321, 273, 224, 172, 118, 61, 2, 2, 61,
		118, 172, 224, 273, 321, 366, 410, 451, 490, 528, 564, 597, 629, 659,
		688, 715, 740, 764, 786, 807, 827, 845, 862, 877, 892, 905, 917, 928,
		938, 948, 956, 963, 970, 975, 981, 985, 989, 992, 994, 997, 998, 1000,
		1001, 1001, 1002, 1002, 1002, 1002,

};


const int blue_dutys[] = { 1002, 1002, 1002, 1002, 1001, 1001, 1000, 998, 997,
		994, 992, 989, 985, 981, 975, 970, 963, 956, 948, 938, 928, 917, 905,
		892, 877, 862, 845, 827, 807, 786, 764, 740, 715, 688, 659, 629, 597,
		564, 528, 490, 451, 410, 366, 321, 321, 321, 321, 321,321, 321, 321, 321,
		321, 321, 321, 321, 321, 366, 410, 451, 490, 528, 564, 597, 629, 659,
		688, 715, 740, 764, 786, 807, 827, 845, 862, 877, 892, 905, 917, 928,
		938, 948, 956, 963, 970, 975, 981, 985, 989, 992, 994, 997, 998, 1000,
		1001, 1001, 1002, 1002, 1002, 1002,

};

void GLED_Sequence()
{

	TACCR2 = led_dutys2[gseq]; //change TA0.1 duty cycle
	gseq++;
	if(gseq>99)
		gseq=0;
}

void RLED_Sequence()
{
	TA1CCR2 = led_dutys2[rseq]; //change TA0.1 duty cycle
	rseq++;
	if(rseq>99)
		rseq=0;
}

void BLED_Sequence()
{
	TACCR1 = led_dutys2[bseq]; //change TA0.1 duty cycle
	bseq++;
	if(bseq>99)
		bseq=0;
}

void fadeRgb()
{
	BLED_Sequence();
	RLED_Sequence();
	GLED_Sequence();
}

void rgbOff()
{
	BLED_A_OFF;
	GLED_A_OFF;
	RLED_A_OFF;
}

void rgbOn()
{
	BLED_A_ON;
	GLED_A_ON;
	RLED_A_ON;
}


void setupRGB()
{
	BLED_A_ON;
	GLED_A_ON;
	RLED_A_ON;
	TA1CCR0 = 1002; // PWM Period
	TACCR0 = 1002;
	TACCTL1 = OUTMOD_7; // CCR1 reset/set
	TACCTL2 = OUTMOD_7; // CCR1 reset/set
	TA1CCTL2 = OUTMOD_7;
	TACCR1 = 10; // CCR1 PWM duty cycle
	TACCR2 = 10; // CCR1 PWM duty cycle
	TA1CCR2 = 10; // CCR1 PWM duty cycle
	TA1CTL = TASSEL_2 + MC_1; // SMCLK, up mode
	TACTL = TASSEL_2 + MC_1; // SMCLK, up mode


	__enable_interrupt(); //Guess
	rgbOff();

}

