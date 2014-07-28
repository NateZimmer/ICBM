/*
 * pwm.c
 *
 *  Created on: Jun 8, 2014
 *      Author: Nate
 */

/*
  	This file is part of MSP430 DAC.
    MSP430 DAC is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MSP430 DAC is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MSP430 DAC.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "adc.h"
#include "pwm.h"

void channelPwmSetup(PWM_PINS PWM_PIN,uint16_t timerValue)
{
	switch(PWM_PIN)
	{
	case P1x2_TA0x1:
		P1DIR |= BIT2;
		P1SEL |= BIT2;
		break;
	case P1x6_TA0x1:
		P1DIR |= BIT6;
		P1SEL |= BIT6;
		break;

	case P2x1_TA1x1:
		P2DIR |= BIT1;
		P2SEL |= BIT1;
		break;

	case P2x2_TA1x1:
		P2DIR |= BIT2;
		P2SEL |= BIT2;
		break;

	case P2x4_TA1x2:
		P2DIR |= BIT4;
		P2SEL |= BIT4;
		break;

	case P2x5_TA1x2:
		P2DIR |= BIT5;
		P2SEL |= BIT5;
		break;
	}

	if(PWM_PIN & (P1x2_TA0x1|P1x6_TA0x1))
	{
		TA0CCR1 = timerValue;
		TA0CCTL1 = OUTMOD_7; // CCR1 reset/set
	}

	if(PWM_PIN & (	P2x1_TA1x1|P2x2_TA1x1))
	{
		TA1CCR1 = timerValue;
		TA1CCTL1 = OUTMOD_7; // CCR1 reset/set
	}

	if(PWM_PIN & (P2x4_TA1x2|P2x5_TA1x2))
	{
		TA1CCR2 = timerValue;
		TA1CCTL2 = OUTMOD_7; // CCR1 reset/set
	}
}

void timerSetup(TIMER_SELECT TIMER, uint16_t timerValue,PWM_CLK_SELECT PWM_CLK,PWM_COUNT_MODE PWM_MODE, PWM_DIVIDER PWM_DIVIDE, bool ISR_ENABLED )
{
	uint16_t TACTL_Value = 0;
	switch(PWM_CLK)
	{
	case TACLK:
		TACTL_Value |= TASSEL_0;
		break;

	case ACLK:
		TACTL_Value |= TASSEL_1;
		break;

	case SMCLK:
		TACTL_Value |= TASSEL_2;
		break;

	case INCLK:
		TACTL_Value |= TASSEL_3;
		break;

	default:
		TACTL_Value |= TASSEL_2;
		break;
	}

	switch(PWM_MODE)
	{
	case STOP:
		TACTL_Value |=MC_0;
		break;

	case UP_TO_CCR0:
		TACTL_Value |=MC_1;
		break;

	case CONTINOUS_UP:
		TACTL_Value |=MC_2;
		break;

	case UP_DOWN:
		TACTL_Value |=MC_3;
		break;

	default:
		break;
	}

	switch(PWM_DIVIDE)
	{
	case ONE_DIVIDER:
		TACTL_Value |=ID_0;
		break;

	case TWO_DIVIDER:
		TACTL_Value |=ID_1;
		break;

	case FOUR_DIVIDER:
		TACTL_Value |=ID_2;
		break;

	case EIGHT_DIVIDER:
		TACTL_Value |=ID_3;
		break;

	default:
		break;
	}

	switch(TIMER)
	{
	case TIMER0:
		TA0CTL =TACTL_Value;
		TA0CCR0 = timerValue;
		if(ISR_ENABLED)
		{
			TA0CCTL0 |= CCIE;
		}
		break;

	case TIMER1:
		TA1CTL =TACTL_Value;
		TA1CCR0 = timerValue;
		if(ISR_ENABLED)
		{
			TA1CCTL0 |= CCIE;
		}
		break;
	}
}

/*
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A1 (void)
{

}
*/

/*
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void)
{



}
*/

