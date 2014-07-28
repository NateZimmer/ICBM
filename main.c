/*
 * main.c
 */

//Author: Nathan Zimmerman

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
