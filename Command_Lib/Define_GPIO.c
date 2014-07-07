/*
 * Define_GPIO.c
 *
 *  Created on: Jul 4, 2014
 *      Author: Nate
 */


#include "Define_GPIO.h"


// AT+DEFINE_GPIO,Port1,[Gpio_Pin],[OutputType],[PullType]

// GPIO_OUTPUT_TYPES=	GPIO_INPUT = 0, GPIO_OUTPUT = 1
// GPIO_PULL_TYPES = GPIO_NO_PULL = 0,	GPIO_PULL_UP = 1,	GPIO_PULL_DOWN = 2


bool Define_GPIO_Value(char * Input_Text)
{
	bool returnVal = false;
	uint16_t GPIO_PIN = 0;
	uint16_t Output_Type_Value=0;
	uint16_t Pull_Type_Value=0;
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
	Input_PTR = Get_Hex_Value(Input_PTR,&Output_Type_Value);
	if(Input_PTR==0)
	{
		return false;
	}
	Input_PTR = Get_Hex_Value(Input_PTR,&Pull_Type_Value);
	if(Input_PTR==0)
	{
		return false;
	}
	Define_GPIO(AT_PORT, (GPIO_OUTPUT_TYPES)Output_Type_Value, (GPIO_PULL_TYPES)(Pull_Type_Value),GPIO_PIN);
	returnVal = true;
	return returnVal;
}


