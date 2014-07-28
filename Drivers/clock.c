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



