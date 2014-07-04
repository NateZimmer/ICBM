/*
 * gpio.h
 *
 *  Created on: Jun 29, 2014
 *      Author: Nate
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "msp430g2553.h"
#include "stdint.h"
#include "stdbool.h"


typedef enum
{
	GPIO_PORT1 = 0,
	GPIO_PORT2 = 1,
	GPIO_PORT3 = 2,
	GPIO_NO_PORT=3
}GPIO_PORTS;

typedef enum
{
	GPIO_INPUT = 0,
	GPIO_OUTPUT = 1
}GPIO_OUTPUT_TYPES;

typedef enum
{
	GPIO_NO_PULL = 0,
	GPIO_PULL_UP = 1,
	GPIO_PULL_DOWN = 2
}GPIO_PULL_TYPES;

typedef struct
{
	GPIO_PORTS GPIO_PORT;
	GPIO_OUTPUT_TYPES GPIO_OUTPUT_TYPE;
	GPIO_PULL_TYPES GPIO_PULL_TYPE;
	uint16_t GPIO_Input_Pin;
}GPIO_INFOS;


bool Read_Digital_Input(GPIO_PORTS GPIO_PORT, uint16_t GPIO_Input_Pin);
void Set_Digital_Output(GPIO_PORTS GPIO_PORT,uint16_t GPIO_PIN, bool Output_High);
uint16_t Read_Digital_Port(GPIO_PORTS GPIO_Port);
void Define_GPIO(GPIO_PORTS GPIO_PORT, GPIO_OUTPUT_TYPES GPIO_OUTPUT_TYPE, GPIO_PULL_TYPES GPIO_PULL_TYPE, uint16_t GPIO_Input_Pin);

#endif /* GPIO_H_ */
