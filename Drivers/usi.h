/*
 * usi.h
 *
 *  Created on: Nov 9, 2013
 *      Author: Nate
 */

#ifndef USI_H_
#define USI_H_

#include "stdint.h"
#include "stdbool.h"

#define UART_TXD_A	BIT2
#define UART_RXD_A	BIT1
#define UART_BUFFER_LEN 100

#define		SLOW_SPI		UCB0BR0 = 0x5 // Down Clock
#define		SLOW2_SPI		UCB0BR0 = 0xA // Down Clock
#define		FAST_SPI		UCB0BR0 = 0x0 //Max

typedef enum
{
	UART,
	SPI
	//I2C
}SERIAL_TYPES;

typedef enum
{
	BAUD_9600,
	BAUD_115200,
	SMCLK_16MHZ_SPI_CLK_4MHZ,
	BAUD_MAX
}BAUD_RATES;

typedef enum
{
	MODULE_A,
	MODULE_B
}MODULES;

typedef struct
{
	SERIAL_TYPES serialType;
	BAUD_RATES baudRate;
	MODULES module;
}SERIAL_CLASSES;


void initUSI(SERIAL_CLASSES * serialClass);
void writeStringTXD(char * data , SERIAL_CLASSES * serialClass);
uint8_t readUsiBuffer(SERIAL_CLASSES * serialClass, uint8_t * pBuf, uint8_t len);
uint8_t getReceivedLength();
void clearRXHead();
uint8_t writeReadByte(uint8_t data);
void writeUartString(char * data);


extern char rx0Buf[UART_BUFFER_LEN];
bool blockOnOk();
bool getOkBlockState();
void resetOkBlockState();
void resetErrorBlockState();
bool getErrorBlockState();
uint16_t getFilteredWeight();



#endif /* USI_H_ */
