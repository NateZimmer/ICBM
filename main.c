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
	char Test_Command[] = "AT+GET_ADC";
	char * Test_PTR;
	Test_PTR = Test_Command;
	AT_COMMANDS AT_COMMAND = NO_COMMAND;
	GPIO_PORTS GPIO_PORT = GPIO_NO_PORT;
	P1DIR = 0;
	P1OUT = 0;
	setupCoreClock(CLK_16_MHZ);
	disableWDT();
	uint16_t Test_Number = 0;
	initADC(BIT0 + BIT3+BIT4+BIT5+BIT6+BIT7);
	initUSI(&uartType);
	_enable_interrupts();
	writeUartString("\033[2J");
	writeUartString("Hello World!! ADC TEST3\r\n");
	while(1)
	{
		Run_Command(Test_Command);
		_delay_cycles(16000000);
	}

	/*
	do
	{
		writeUartString(Test_PTR);
		writeUartString("\r\n");
		Test_PTR = Check_For_AT(Test_PTR);
		if(Test_PTR)
		{
			writeUartString(Test_PTR);
			writeUartString("\r\n");
		}
		else
		{
			break;
		}
		Test_PTR = Get_AT_Command(Test_PTR,&AT_COMMAND);
		if(Test_PTR)
		{
			writeUartString(Test_PTR);
			writeUartString("\r\n");
		}
		else
		{
			break;
		}
		Test_PTR = AT_Get_Port(Test_PTR,&GPIO_PORT);
		if(Test_PTR)
		{
			writeUartString(Test_PTR);
			writeUartString("\r\n");
		}
		else
		{
			break;
		}
		Test_PTR = Get_Hex_Value(Test_PTR,&Test_Number);
		if(Test_PTR)
		{
			writeUartString(Test_PTR);
			writeUartString("\r\n");
		}
		else
		{
			break;
		}
		Test_PTR = Get_Hex_Value(Test_PTR,&Test_Number);
		if(Test_PTR)
		{
			writeUartString(Test_PTR);
			writeUartString("\r\n");
		}
		else
		{
			break;
		}

		DEBUG();

	}while(0);
*/

	while(1);


}
