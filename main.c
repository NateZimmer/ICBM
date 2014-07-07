/*
 * main.c
 */

#include "Parse_Command.h"
#include "Drivers/Nates_Driver_Set.h"
#include "Run_Commands.h"

SERIAL_CLASSES uartType = {UART,BAUD_9600,MODULE_A};

void main(void) {
	//char Test_Command[] = "AT+DEFINE_GPIO,PORT1,0x1,1,0";
	//char Test_Command2[] = "AT+SET_OUTPUT,PORT1,0x1,1";
	//char Test_Command[] = "AT+READ_DIGITAL,PORT1";
	//char Test_Command[] = "AT+GET_ADC";
	P1DIR = 0;
	P1OUT = 0;
	P2SEL = 0;
	P2SEL2 = 0;
	setupCoreClock(CLK_16_MHZ);
	disableWDT();
	initADC(0); // exploit erata to make this work



	initUSI(&uartType);
	_enable_interrupts();
	//writeUartString("\033[2J");
	//writeUartString("Hello World!! ADC TEST3\r\n");

	while(1);
}
