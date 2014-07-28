/*
 * adc.c
 *
 *  Created on: Nov 9, 2013
 *      Author: Nate
 */


/*
 * This code automatically samples the ADC without using an external timer.
 */

#include  "msp430g2553.h"
#include "adc.h"

typedef union {
	adcChannels adcChannel;
	unsigned int dataArray[8];
} adcData;

static adcData ADC10;
static adcData ADC10_External;

void initADC(unsigned int inputBits) {
	ADC10CTL1 = INCH_7 + CONSEQ_1; // Start sequence at channel 7, then decrement to A0
	ADC10AE0 = inputBits;
	ADC10CTL0 = ADC10SHT_2 + MSC + ADC10ON + ADC10IE; //See definitions
	ADC10DTC1 = 0x08; // 8 conversions
	ADC10CTL0 &= ~ENC;
	while (ADC10CTL1 & BUSY); // Wait if ADC10 core is active
	ADC10SA = (unsigned int) ADC10.dataArray; // Data buffer start
	ADC10CTL0 |= ENC + ADC10SC; // Sampling and conversion start
	_enable_interrupts();
}

adcChannels getAdcData()
{
	return ADC10_External.adcChannel;
}

uint16_t getAdcBufferAddress()
{
	return (uint16_t)(&ADC10.dataArray[0]);
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void) {
	_delay_cycles(10); // Erata Delay
	ADC10_External.dataArray[0]=ADC10.dataArray[0];
	ADC10_External.dataArray[1]=ADC10.dataArray[1];
	ADC10_External.dataArray[2]=ADC10.dataArray[2];
	ADC10_External.dataArray[3]=ADC10.dataArray[3];
	ADC10_External.dataArray[4]=ADC10.dataArray[4];
	ADC10_External.dataArray[5]=ADC10.dataArray[5];
	ADC10_External.dataArray[6]=ADC10.dataArray[6];
	ADC10_External.dataArray[7]=ADC10.dataArray[7];
	ADC10CTL0 &= ~ENC;
	ADC10SA = (unsigned int) getAdcBufferAddress(); // Data buffer start
	ADC10CTL0 |= ENC + ADC10SC; // Sampling and conversion start

}

