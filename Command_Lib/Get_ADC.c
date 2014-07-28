/*
 * Get_ADC.c
 *
 *  Created on: Jul 4, 2014
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

#include "Get_ADC.h"

bool Get_Adc_Values()
{
	adcChannels adcData = getAdcData();
	sprintf(outputTextBuffer,"\r\n%d,",adcData.A0); // A1 and A2 are comm lines, hence they are skipped
	writeUartString(outputTextBuffer);
	sprintf(outputTextBuffer,"%d,",adcData.A3);
	writeUartString(outputTextBuffer);
	sprintf(outputTextBuffer,"%d,",adcData.A4);
	writeUartString(outputTextBuffer);
	sprintf(outputTextBuffer,"%d,",adcData.A5);
	writeUartString(outputTextBuffer);
	sprintf(outputTextBuffer,"%d,",adcData.A6);
	writeUartString(outputTextBuffer);
	sprintf(outputTextBuffer,"%d\r\n",adcData.A7);
	writeUartString(outputTextBuffer);
	return true;
}

