/*
 * Read_Digital.c
 *
 *  Created on: Jul 4, 2014
 *      Author: Nate
 */

#include "Read_Digital.h"

bool Read_Digital(char * Input_Text)
{
	uint16_t Port_1_Data = Read_Digital_Port(GPIO_PORT1);
	uint16_t Port_2_Data = Read_Digital_Port(GPIO_PORT2);
	sprintf(outputTextBuffer,"\r\n%d,%d\r\n",Port_1_Data,Port_2_Data);
	writeUartString(outputTextBuffer);
	return true;
}
