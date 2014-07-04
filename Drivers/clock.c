/*
 * clock.c
 *
 *  Created on: Nov 6, 2013
 *      Author: Nate
 */

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



