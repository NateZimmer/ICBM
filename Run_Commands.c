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


char Command_Buffer[40];

static uint16_t Command_Buffer_Index = 0;

void Add_Char_To_Command_Buffer(char Input_Char)
{
	Command_Buffer[Command_Buffer_Index] = Input_Char;
	Command_Buffer_Index = (Command_Buffer_Index + 1) % (sizeof(Command_Buffer)-1);
}

void Clear_Command_Buffer()
{
	Command_Buffer_Index = 0;
	memset(Command_Buffer,0,sizeof(Command_Buffer));
}

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

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void) {
	char Input_Char = 0;
	if((IFG2 & UCA0RXIFG))
	{
		Input_Char =UCA0RXBUF;
		if(Input_Char == '\r')
		{
			Run_Command(Command_Buffer);
			Clear_Command_Buffer();
		}
		else
		{
			while (!(IFG2 & UCA0TXIFG));
			UCA0TXBUF = Input_Char;
			//while (UCA0STAT & UCBUSY);
			Add_Char_To_Command_Buffer(Input_Char);
		}
	}

	if((IFG2 & UCB0RXIFG))
	{
		_delay_cycles(1);
	}
}



