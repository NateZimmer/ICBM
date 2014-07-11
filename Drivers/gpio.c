/*
 * gpio.c
 *
 *  Created on: Jun 29, 2014
 *      Author: Nate
 */

#include "gpio.h"

bool Read_Digital_Input(GPIO_PORTS GPIO_PORT, uint16_t GPIO_Input_Pin)
{
	bool returnVal = false;

	switch(GPIO_PORT)
	{
	case GPIO_PORT1:
		if(P1IN & (GPIO_Input_Pin))
		{
			returnVal =true;
		}
		break;
	case GPIO_PORT2:
		if(P2IN & (GPIO_Input_Pin))
		{
			returnVal =true;
		}
		break;
	case GPIO_PORT3:
		if(P3IN & (GPIO_Input_Pin))
		{
			returnVal =true;
		}
		break;
	default:
		break;
	}
	return returnVal;
}

void Set_Digital_Output(GPIO_PORTS GPIO_PORT,uint16_t GPIO_PIN, bool Output_High)
{
	switch(GPIO_PORT)
	{
	case GPIO_PORT1:
		if(Output_High)
		{
			P1OUT |= (GPIO_PIN);
		}
		else
		{
			P1OUT &= (~GPIO_PIN)|(BIT1+BIT2);
		}
		P1SEL &= (~GPIO_PIN)|(BIT1+BIT2);
		P1SEL2 &= (~GPIO_PIN)|(BIT1+BIT2);
		break;
	case GPIO_PORT2:
		if(Output_High)
		{
			P2OUT |= (GPIO_PIN);
		}
		else
		{
			P2OUT &= ~(GPIO_PIN);
		}
		P2SEL &= (~GPIO_PIN);
		P2SEL2 &= (~GPIO_PIN);
		break;
	case GPIO_PORT3:
		if(Output_High)
		{
			P3OUT |= (GPIO_PIN);
		}
		else
		{
			P3OUT &= ~(GPIO_PIN);
		}
		P3SEL &= (~GPIO_PIN);
		P3SEL2 &= (~GPIO_PIN);
		break;
	default:
		break;
	}
}

uint16_t Read_Digital_Port(GPIO_PORTS GPIO_Port)
{
	uint16_t returnVal=0;
	switch(GPIO_Port)
	{
	case GPIO_PORT1:
		returnVal = P1IN;
		break;
	case GPIO_PORT2:
		returnVal = P2IN;
		break;
	case GPIO_PORT3:
		returnVal = P3IN;
		break;
	default:
		break;
	}
	return returnVal;
}

void Define_GPIO(GPIO_PORTS GPIO_PORT, GPIO_OUTPUT_TYPES GPIO_OUTPUT_TYPE, GPIO_PULL_TYPES GPIO_PULL_TYPE, uint16_t GPIO_Input_Pin)
{
	switch(GPIO_PORT)
	{
	case GPIO_PORT1:
		if(GPIO_OUTPUT_TYPE == GPIO_OUTPUT)
		{
			P1DIR |= GPIO_Input_Pin;
			P1REN &=~GPIO_Input_Pin;
		}
		else
		{
			P1DIR &=(~GPIO_Input_Pin)|(BIT1+BIT2);
			switch(GPIO_PULL_TYPE)
			{
			case GPIO_NO_PULL:
				P1REN &=~(GPIO_Input_Pin);
				break;
			case GPIO_PULL_UP:
				P1REN |=(GPIO_Input_Pin);
				P1OUT |=(GPIO_Input_Pin);
				break;
			case GPIO_PULL_DOWN:
				P1REN |=(GPIO_Input_Pin);
				P1OUT &=~(GPIO_Input_Pin);
				break;
			default:
				break;
			}
		}
	case GPIO_PORT2:
		if(GPIO_OUTPUT_TYPE == GPIO_OUTPUT)
		{
			P2DIR |=GPIO_Input_Pin;
		}
		else
		{
			P2DIR &=~(GPIO_Input_Pin);
			switch(GPIO_PULL_TYPE)
			{
			case GPIO_NO_PULL:
				P2REN &=~(GPIO_Input_Pin);
				break;
			case GPIO_PULL_UP:
				P2REN |=(GPIO_Input_Pin);
				P2OUT |=(GPIO_Input_Pin);
				break;
			case GPIO_PULL_DOWN:
				P2REN |=(GPIO_Input_Pin);
				P2OUT &=~(GPIO_Input_Pin);
				break;
			default:
				break;
			}
		}
	case GPIO_PORT3:
		if(GPIO_OUTPUT_TYPE == GPIO_OUTPUT)
		{
			P3DIR |= GPIO_Input_Pin;
		}
		else
		{
			P3DIR &=~(GPIO_Input_Pin);
			switch(GPIO_PULL_TYPE)
			{
			case GPIO_NO_PULL:
				P3REN &=~(GPIO_Input_Pin);
				break;
			case GPIO_PULL_UP:
				P3REN |=(GPIO_Input_Pin);
				P3OUT |=(GPIO_Input_Pin);
				break;
			case GPIO_PULL_DOWN:
				P3REN |=(GPIO_Input_Pin);
				P3OUT &=~(GPIO_Input_Pin);
				break;
			default:
				break;
			}
		}
	default:
		break;
	}
}





