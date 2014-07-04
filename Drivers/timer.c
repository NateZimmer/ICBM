/*
 * timer.c
 *
 *  Created on: Mar 30, 2014
 *      Author: Nate
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
