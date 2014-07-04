/*
 * Set_GPIO_Output.c
 *
 *  Created on: Jul 4, 2014
 *      Author: Nate
 */

#include "Set_GPIO_Output.h"

bool Set_GPIO_Output(char * Input_Text)
{
	bool returnVal = false;
	uint16_t GPIO_PIN = 0;
	uint16_t outputHigh=0;
 	GPIO_PORTS AT_PORT = GPIO_NO_PORT;

	char * Input_PTR = Input_Text;
	Input_PTR =AT_Get_Port(Input_PTR, &AT_PORT);
	if(Input_PTR==0)
	{
		return false;
	}
	_delay_cycles(1);
	Input_PTR = Get_Hex_Value(Input_PTR,&GPIO_PIN);
	if(Input_PTR==0)
	{
		return false;
	}
	Input_PTR = Get_Hex_Value(Input_PTR,&outputHigh);
	if(Input_PTR==0)
	{
		return false;
	}
	Set_Digital_Output(AT_PORT,GPIO_PIN,(bool)outputHigh);
	returnVal = true;
	return returnVal;
}


