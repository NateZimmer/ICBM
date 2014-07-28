/*
 * rtc.c
 *
 *  Created on: Apr 6, 2013
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

