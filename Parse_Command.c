/*
 * Parse_Command.c
 *
 *  Created on: Jul 4, 2014
 *      Author: Nate
 */

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

#define PTR_SIZE uint16_t

const char * AT= "AT+";
const char * AT_READ_DIGITAL="READ_DIGITAL";
const char * AT_SET_OUTPUT = "SET_OUTPUT";
const char * AT_DEFINE_GPIO = "DEFINE_GPIO";
const char * AT_ACK = "ACK";
const char * AT_GET_ADC="GET_ADC";
const char * AT_PORT_1 =",PORT1";
const char * AT_PORT_2 =",PORT2";
const char * AT_PORT_3 =",PORT3";
const char * AT_PWM ="PWM";
const char * AT_SPI_CONFIG = "SPI_CONFIG";
const char * AT_SPI_SEND = "SPI_SEND";
const char * AT_INVALID = "\r\nInvalid Message\r\n";

//Checks for the string "AT+" and returns the pointer to the location past this if it is included in the string

char outputTextBuffer[30];


char * Check_For_AT(char * Input_String)
{
	char * returnVal;
	returnVal = strstr((const char *)Input_String,AT);
	if(returnVal)
	{
		returnVal +=strlen(AT);
	}
	return returnVal;
}

// This function gets the AT command from a string of "AT+"

char * Get_AT_Command(char * Input_String,AT_COMMANDS *AT_COMMAND)
{
	*AT_COMMAND = NO_COMMAND;
	char * returnVal = 0;
	returnVal =strstr((const char *)Input_String,AT_READ_DIGITAL);
	if(returnVal)
	{
		*AT_COMMAND = READ_DIGITAL_INPUTS;
		returnVal+=strlen(AT_READ_DIGITAL);
		return returnVal;

	}
	returnVal = strstr((const char *)Input_String,AT_SET_OUTPUT);
	if(returnVal)
	{
		*AT_COMMAND = SET_GPIO_OUTPUT;
		returnVal+=strlen(AT_SET_OUTPUT);
		return returnVal;
	}
	returnVal = strstr((const char *)Input_String,AT_GET_ADC);
	if(returnVal)
	{
		*AT_COMMAND = READ_ADC;
		returnVal+=strlen(AT_GET_ADC);
		return returnVal;
	}
	returnVal = strstr((const char *)Input_String,AT_DEFINE_GPIO);
	if(returnVal)
	{
		*AT_COMMAND = DEFINE_GPIO;
		returnVal+=strlen(AT_DEFINE_GPIO);
		return returnVal;
	}
	returnVal = strstr((const char *)Input_String,AT_ACK);
	if(returnVal)
	{
		*AT_COMMAND = ACK;
		returnVal+=strlen(AT_ACK);
		return returnVal;
	}
	returnVal = strstr((const char *)Input_String,AT_PWM);
	if(returnVal)
	{
		*AT_COMMAND = SET_PWM;
		returnVal+=strlen(AT_PWM);
		return returnVal;
	}
	returnVal = strstr((const char *)Input_String,AT_SPI_CONFIG);
	if(returnVal)
	{
		*AT_COMMAND =CONFIG_SPI;
		returnVal+=strlen(AT_SPI_CONFIG);
		return returnVal;
	}
	returnVal = strstr((const char *)Input_String,AT_SPI_SEND);
	if(returnVal)
	{
		*AT_COMMAND = SEND_SPI;
		returnVal+=strlen(AT_SPI_SEND);
		return returnVal;
	}
	return returnVal;
}

char * AT_Get_Port(char * Input_String, GPIO_PORTS * GPIO_PORT)
{
	char * returnVal = 0;
	returnVal =strstr((const char *)Input_String,AT_PORT_1);
	if(returnVal)
	{
		*GPIO_PORT = GPIO_PORT1;
		returnVal+=strlen(AT_PORT_1);
		return returnVal;

	}
	returnVal = strstr((const char *)Input_String,AT_PORT_2);
	if(returnVal)
	{
		*GPIO_PORT = GPIO_PORT2;
		returnVal+=strlen(AT_PORT_1);
		return returnVal;
	}
	returnVal = strstr((const char *)Input_String,AT_PORT_3);
	if(returnVal)
	{
		*GPIO_PORT = GPIO_PORT3;
		returnVal+=strlen(AT_PORT_1);
		return returnVal;
	}
	return returnVal;
}

char * Get_Hex_Value(char * Input_String,uint16_t  * Hex_Value)
{
	char * returnVal;
	char * tempPtr;
	tempPtr=Input_String;
	if(tempPtr[0]==',')
	{
		tempPtr++;
	}
	*Hex_Value = (uint16_t)strtoul((const char *)tempPtr,&returnVal,16);
	return returnVal;
}
