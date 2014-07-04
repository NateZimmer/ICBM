/*
 * Run_Commands.c
 *
 *  Created on: Jul 4, 2014
 *      Author: Nate
 */


#include "Parse_Command.h"
#include "Run_Commands.h"

#include "Command_Lib/Read_Digital.h"
#include "Command_Lib/Set_GPIO_Output.h"
#include "Command_Lib/Define_GPIO.h"
#include "Command_Lib/Get_ADC.h"

void Run_Command(char * Input_Text)
{
 	bool returnVal = false;
 	AT_COMMANDS AT_Command;
 	extern char * AT_INVALID;
	do
 	{
 		Input_Text = Check_For_AT(Input_Text);
 		if(Input_Text==0)
 		{
 			break;
 		}
 		Input_Text = Get_AT_Command(Input_Text,&AT_Command);
 		if(Input_Text==0)
 		{
 			break;
 		}
 		else
 		{
 			switch(AT_Command)
 			{
 			case DEFINE_GPIO:
 				if(Define_GPIO_Value(Input_Text))
 				{
 					returnVal = true;
 				}
 				break;
 			case SET_GPIO_OUTPUT:
 				if(Set_GPIO_Output(Input_Text))
 				{
 					returnVal = true;
 				}
 				break;
 			case READ_DIGITAL_INPUTS:
 				if(Read_Digital(Input_Text))
 				{
 					returnVal = true;
 				}
 				break;
 			case READ_ADC:
 				if(Get_Adc_Values())
 				{
 					returnVal = true;
 				}
 				break;
 			case NO_COMMAND:
 				break;
 			default:
 				break;
 			}
 		}
 	}while(0);
	if(!returnVal)
	{
		writeUartString((char *)AT_INVALID);
	}
}
