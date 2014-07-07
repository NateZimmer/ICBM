/*
 * Get_ADC.c
 *
 *  Created on: Jul 4, 2014
 *      Author: Nate
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

