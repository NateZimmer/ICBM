/*
 * adc.h
 *
 *  Created on: Nov 9, 2013
 *      Author: Nate
 */

#ifndef ADC_H_
#define ADC_H_

#include "msp430g2553.h"
#include "stdint.h"

typedef struct {
	unsigned int A7;
	unsigned int A6;
	unsigned int A5;
	unsigned int A4;
	unsigned int A3;
	unsigned int A2;
	unsigned int A1;
	unsigned int A0;

} adcChannels;

adcChannels getAdcData();
void initADC(unsigned int inputBits);
uint16_t getAdcBufferAddress();

#endif /* ADC_H_ */
