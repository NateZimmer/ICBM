/*
 * Parse_Command.h
 *
 *  Created on: Jul 4, 2014
 *      Author: Nate
 */

#ifndef PARSE_COMMAND_H_
#define PARSE_COMMAND_H_

#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "msp430g2553.h"
#include "Drivers/Nates_Driver_Set.h"

typedef enum
{
	NO_COMMAND=0,
	DEFINE_GPIO= 1,
	SET_GPIO_OUTPUT=2,
	READ_DIGITAL_INPUTS=3,
	READ_ADC=4
}AT_COMMANDS;

#define DEBUG()	_delay_cycles(1)

char * Check_For_AT(char * Input_String);
char * Get_AT_Command(char * Input_String,AT_COMMANDS *AT_COMMAND);
char * AT_Get_Port(char * Input_String, GPIO_PORTS * GPIO_PORT);
char * Get_Hex_Value(char * Input_String,uint16_t  * Hex_Value);

extern char outputTextBuffer[30];


#endif /* PARSE_COMMAND_H_ */
