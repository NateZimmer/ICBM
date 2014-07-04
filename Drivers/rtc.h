/*
 * rtc.h
 *
 *  Created on: Apr 6, 2013
 *      Author: Nate
 */

#ifndef RTC_H_
#define RTC_H_

#include "stdint.h"

// System count time

// 1  count  =  15.6ms
// 2  counts =  31.6ms
// 4  counts =  62.5ms
// 8  counts = 125.0ms
// 16 counts = 250.0ms
// 32 counts = 500.0ms

typedef struct
{
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
}SYSTEM_TIME;

void setupRtcTick();
void disableWDT();
uint8_t get_system_tick();
uint16_t getSystemSeconds();
void clearSystemTime();
void getSystemTime(SYSTEM_TIME * systemValues);




#endif /* RTC_H_ */
