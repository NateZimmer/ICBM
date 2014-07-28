/*
 * Set_PWM.c
 *
 *  Created on: Jul 9, 2014
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

#include "Set_PWM.h"

//AT+PWM,[PIN],[Freq/CCR0],[Duty],[Divider]
//AT+PWM,1,60000,60000,1

bool Set_PWM_Output(char * Input_Text)
{
	bool returnVal = false;
	uint16_t GPIO_PIN = 0;
	uint16_t CCR0_Value = 0;
	uint16_t CCRX_Value = 0;
	uint16_t Divider = 0;

	char * Input_PTR = Input_Text;
	Input_PTR =Get_Hex_Value(Input_PTR,&GPIO_PIN);
	if(Input_PTR==0)
	{
		return false;
	}
	_delay_cycles(1);
	Input_PTR = Get_Hex_Value(Input_PTR,&CCR0_Value);
	if(Input_PTR==0)
	{
		return false;
	}
	Input_PTR = Get_Hex_Value(Input_PTR,&CCRX_Value);
	if(Input_PTR==0)
	{
		return false;
	}
	Input_PTR = Get_Hex_Value(Input_PTR,&Divider);
	if(Input_PTR==0)
	{
		return false;
	}

	if(GPIO_PIN>1)
	{
		timerSetup(TIMER1, CCR0_Value,SMCLK,UP_TO_CCR0,(PWM_DIVIDER)Divider,false);
		channelPwmSetup((PWM_PINS)GPIO_PIN,CCRX_Value);
	}
	else
	{
		timerSetup(TIMER0, CCR0_Value,SMCLK,UP_TO_CCR0,(PWM_DIVIDER)Divider,false);
		channelPwmSetup((PWM_PINS)GPIO_PIN,CCRX_Value);
	}
	returnVal = true;
	return returnVal;
}

