/*
 * Serial_Data.c
 *
 *  Created on: Jul 26, 2014
 *      Author: Nate
 */

#include "Serial_Data.h"


#define DATA_BUFFER_LENGTH 10

static uint8_t Data_Buffer[DATA_BUFFER_LENGTH];
static uint8_t Recieve_Buffer[DATA_BUFFER_LENGTH];

//AT+SPI_CONFIG,[Phase/Polarity],[Baud Rate]; //This configures the SPI

bool Define_Spi(char * Input_Text)
{
	bool returnVal = false;
	uint16_t Baud_Rate = 0;
	uint16_t Phase_Polarity = 0;
	char * Input_PTR = Input_Text;
	do
	{
		Input_PTR =Get_Hex_Value(Input_PTR,&Phase_Polarity);
		if(Input_PTR==0)
		{
			break;
		}
		Input_PTR = Get_Hex_Value(Input_PTR,&Baud_Rate);
		if(Input_PTR==0)
		{
			break;
		}
		initSpiBFull(Baud_Rate,(SPI_PHASE_POLARITYS)Phase_Polarity);
		Define_GPIO(GPIO_PORT2,GPIO_OUTPUT,GPIO_NO_PULL,BIT0);
		Set_Digital_Output(GPIO_PORT2,BIT0,true);
		writeUartString("\r\n");
		returnVal = true;
	}while(0);
	return returnVal;
}

//AT+SPI_SEND,Length,Data,Data...ect

bool Send_SPI_Data(char * Input_Text)
{
	bool returnVal = false;
	uint16_t i = 0;
	uint16_t Length = 0;
	uint16_t Data = 0;
	char * Input_PTR = Input_Text;
	do
	{
		Input_PTR =Get_Hex_Value(Input_PTR,&Length);
		if(Input_PTR==0)
		{
			break;
		}
		if(Length>DATA_BUFFER_LENGTH)
		{
			break;
		}
		for(i=0;i<Length;i++)
		{
			Input_PTR = Get_Hex_Value(Input_PTR,&Data);
			if(Input_PTR==0)
			{
				break;
			}
			Data_Buffer[i] = (uint8_t)(Data & 0xFF);
		}
		Set_Digital_Output(GPIO_PORT2,BIT0,true);
		_delay_cycles(1000);
		Set_Digital_Output(GPIO_PORT2,BIT0,false);
		_delay_cycles(1000);
		for(i=0;i<Length;i++)
		{
			Recieve_Buffer[i] = writeReadByte( Data_Buffer[i] );
		}
		Set_Digital_Output(GPIO_PORT2,BIT0,true);
		writeUartString("\r\n");
		for(i=0;i<Length;i++)
		{
			sprintf(outputTextBuffer,"0x%x ",Recieve_Buffer[i]);
			writeUartString(outputTextBuffer);
		}
		writeUartString("\r\n");
		returnVal = true;
	}while(0);
	return returnVal;
}
