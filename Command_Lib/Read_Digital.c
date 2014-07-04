/*
 * Read_Digital.c
 *
 *  Created on: Jul 4, 2014
 *      Author: Nate
 */

#include "Read_Digital.h"

bool Read_Digital(char * Input_Text)
{
	bool returnVal = false;
 	GPIO_PORTS AT_PORT = GPIO_NO_PORT;
	uint16_t Port_Input_Data = 0;
//	extern char * outputTextBuffer;
	if(AT_Get_Port(Input_Text, &AT_PORT))
	{
		Port_Input_Data = Read_Digital_Port(AT_PORT);
		sprintf(outputTextBuffer,"\r\n%d\r\n",Port_Input_Data);
		writeUartString(outputTextBuffer);
		returnVal = true;
	}
	return returnVal;
}
