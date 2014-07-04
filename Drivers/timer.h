/*
 * timer.h
 *
 *  Created on: Mar 30, 2014
 *      Author: Nate
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "stdint.h"
#include "stdbool.h"

typedef struct
{
	uint8_t currentSeconds;
	uint8_t previousSeconds;
}secondCounters;

void runSecondsTimer(secondCounters * secondCounter);
bool checkTimerIfExpired(secondCounters * secondCounter);
void resetTimer(secondCounters * secondCounter , uint8_t timeoutValue);
void startTimer(secondCounters * secondCounter);

#endif /* TIMER_C_ */



