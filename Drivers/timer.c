/*
 * timer.c
 *
 *  Created on: Mar 30, 2014
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

#include "timer.h"
#include "rtc.h"

void startTimer(secondCounters * secondCounter)
{
	secondCounter->previousSeconds = getSystemSeconds();
}

void runSecondsTimer(secondCounters * secondCounter)
{
	uint8_t previousSecond =secondCounter->previousSeconds;
	uint8_t currentSystemSecond = getSystemSeconds();
	if(previousSecond != currentSystemSecond)
	{
		secondCounter->previousSeconds = (secondCounter->previousSeconds + 1)%60;
		if(secondCounter->currentSeconds>0)
		{
			secondCounter->currentSeconds--;
		}
	}
}

bool checkTimerIfExpired(secondCounters * secondCounter)
{
	bool returnVal = false;
	if(secondCounter->currentSeconds == 0)
	{
		returnVal = true;
	}
	return returnVal;
}

void resetTimer(secondCounters * secondCounter , uint8_t timeoutValue)
{
	secondCounter->currentSeconds = timeoutValue;
}
