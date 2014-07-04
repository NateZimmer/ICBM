/*
 * clock.h
 *
 *  Created on: Nov 6, 2013
 *      Author: Nate
 */

#ifndef CLOCK_H_
#define CLOCK_H_

typedef enum
{
	CLK_16_MHZ,
	CLK_12_MHZ,
	CLK_8_MHZ,
	CLK_1MHZ
}clockFreqs;

void setupCoreClock(clockFreqs coreFrequency);
void disableWDT();



#endif /* CLOCK_H_ */
