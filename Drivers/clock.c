/*
 * clock.c
 *
 *  Created on: Nov 6, 2013
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

#include <stdint.h>

#define MHZ_16 16000000
#define MHZ_12 12000000
#define MHZ_8   8000000
#define MHZ_1   1000000
#define A_CRYSTAL 32768
#define DIVIDER 4

#define DCO_CAL_16 (MHZ_16*DIVIDER/A_CRYSTAL)
#define DCO_CAL_12 (MHZ_12*DIVIDER/A_CRYSTAL)
#define DCO_CAL_08 (MHZ_8*DIVIDER/A_CRYSTAL)
#define DCO_CAL_01 (MHZ_1*DIVIDER/A_CRYSTAL)

#include "msp430g2553.h"
#include "clock.h"

void setupCoreClock(clockFreqs coreFrequency)
{
	switch(coreFrequency)
	{
		case CLK_16_MHZ:
			BCSCTL1 = CALBC1_16MHZ;
			DCOCTL = CALDCO_16MHZ;
			break;
		case CLK_12_MHZ:
			BCSCTL1 = CALBC1_12MHZ;
			DCOCTL = CALDCO_12MHZ;
			break;
		case CLK_8_MHZ:
			BCSCTL1 = CALBC1_8MHZ;
			DCOCTL = CALDCO_8MHZ;
			break;
		default:
			BCSCTL1 = CALBC1_1MHZ;
			DCOCTL = CALDCO_1MHZ;
			break;
	}
}

void Set_DCO(unsigned int Delta) {    // Set DCO to selected frequency
	unsigned int Compare, Oldcapture = 0;
	BCSCTL3 |= XCAP_3;       // 12.5 pF for LaunchPad crystal
	__delay_cycles(55000);   // let crystal stabilize
	BCSCTL1 |= DIVA_2;                  // ACLK = LFXT1CLK/8
	TACCTL0 = CM_1 + CCIS_1 + CAP;      // CAP, ACLK
	TACTL = TASSEL_2 + MC_2 + TACLR;    // SMCLK, cont-mode, clear

	while (1) {
	while (!(CCIFG & TACCTL0));       // Wait until capture
									  // occured
	TACCTL0 &= ~CCIFG;                // Capture occured, clear
									  // flag
	Compare = TACCR0;                 // Get current captured
									  // SMCLK
	Compare = Compare - Oldcapture;   // SMCLK difference
	Oldcapture = TACCR0;              // Save current captured
									  // SMCLK


	if (Delta == Compare)
	  break;                          // If equal, leave
									  // "while(1)"
	else if (Delta < Compare) {
	  DCOCTL--;                       // DCO is too fast, slow
									  // it down
	  if (DCOCTL == 0xFF)             // Did DCO roll under?
		if (BCSCTL1 & 0x0f)
		  BCSCTL1--;                  // Select lower RSEL
	}
	else {
	  DCOCTL++;                       // DCO is too slow, speed
									  // it up
	  if (DCOCTL == 0x00)             // Did DCO roll over?
		if ((BCSCTL1 & 0x0f) != 0x0f)
		  BCSCTL1++;                  // Sel higher RSEL
	}
	}
	TACCTL0 = 0;                        // Stop TACCR0
	TACTL = 0;                          // Stop Timer_A
	BCSCTL1 &= ~DIVA_3;                 // ACLK = LFXT1CLK
}

void calibrateDCO(clockFreqs coreFrequency)
{
	volatile uint16_t DCO_Cal_Value = 0;

switch(coreFrequency)
{
	case CLK_16_MHZ:
			DCO_Cal_Value = DCO_CAL_16;

			break;
		case CLK_12_MHZ:
			DCO_Cal_Value = DCO_CAL_12;
			break;
		case CLK_8_MHZ:
			DCO_Cal_Value = DCO_CAL_08;
			break;
		case CLK_1MHZ:
			DCO_Cal_Value = DCO_CAL_01;
			break;
		default:
			break;
}
	if(DCO_Cal_Value)
	{
		Set_DCO(DCO_Cal_Value);
	}
}







