/*
 * rtc.c
 *
 *  Created on: Apr 6, 2013
 *      Author: Nate
 */


#include "msp430g2553.h"
#include "rtc.h"

static uint8_t ticks=0;
static uint16_t timeTicks= 0;
static uint8_t systemSeconds = 0;
static uint8_t systemMinutes = 0;
static uint8_t systemHours = 0;

void disableWDT()
{
	WDTCTL = WDTPW + WDTHOLD;
}

void setupRtcTick()
{
	WDTCTL = WDT_MDLY_32;	// WDT 0.015625ms or 64 Hz
	IE1 |= WDTIE;         	// Enable WDT interrupt
	__enable_interrupt();
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
	ticks++; // Interrupts every 1/64s
	timeTicks++;
	if(timeTicks==490)
	{
		timeTicks=0;
		systemSeconds++;
		if(systemSeconds==60)
		{
			systemSeconds = 0;
			systemMinutes++;
			if(systemMinutes>59)
			{
				systemHours++;
				systemMinutes=0;
			}
		}
	}
}

uint8_t get_system_tick()
{
	return ticks;
}

uint16_t getSystemSeconds()
{
	return systemSeconds;
}

void getSystemTime(SYSTEM_TIME * systemValues)
{
	systemValues->seconds = systemSeconds;
	systemValues->minutes = systemMinutes;
	systemValues->hours = systemHours;
}

void clearSystemTime()
{
	systemSeconds = 0;
	systemMinutes =0;
	systemHours =0;

}

