/*
 * main.c
 */

//Author: Nathan Zimmerman

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


#include "Parse_Command.h"
#include "Drivers/Nates_Driver_Set.h"
#include "Run_Commands.h"

SERIAL_CLASSES uartType = {UART,BAUD_9600,MODULE_A};

void main(void) {
	P1DIR = 0;
	P1OUT = 0;
	P2SEL = 0;
	P2SEL2 = 0;
	setupCoreClock(CLK_16_MHZ);
	disableWDT();
	initADC(0); // exploit erata to make this work
	initUSI(&uartType);
	_enable_interrupts();
	while(1);
}
