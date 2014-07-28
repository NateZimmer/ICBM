/*
 * usi.c
 *
 *  Created on: Nov 9, 2013
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

#include "msp430g2553.h"
#include "usi.h"
#include "stdbool.h"

char rx0Buf[UART_BUFFER_LEN];
static unsigned int rx0Head=0;
static unsigned int rx0Tail=0;
//static uint8_t byteBuffer = 0;

void initUart(SERIAL_CLASSES * uartClass)
{
	switch(uartClass->module)
	{
	case MODULE_A:
        P1SEL |= UART_TXD_A + UART_RXD_A; // Set P1.1 to RXD and P1.2 to TXD
        P1SEL2 |= UART_TXD_A + UART_RXD_A; //
		break;
	default:
		break;
	}
    UCA0CTL1 |= UCSSEL_2;

    switch(uartClass->baudRate)
    {
    case BAUD_9600:
    	UCA0BR1 = (0x682>>8);
    	UCA0BR0 = (0x682 & 0xFF);
    	UCA0MCTL = UCBRS_6;
    	break;
    case BAUD_115200:
    	UCA0BR1 = (0x8A>>8);
        UCA0BR0 = (0x8A & 0xFF);
        UCA0MCTL = UCBRS_7;
    	break;
    default:
    	break;
    }

    UCA0CTL1 &= ~UCSWRST; // Start USCI
    IE2 |= UCA0RXIE; //Enable interrupt for USCI
    P1OUT |= UART_TXD_A + UART_RXD_A;
    __enable_interrupt(); //Guess

}

void initSpiBFull(uint16_t baudRate, SPI_PHASE_POLARITYS SPI_Phase_Polarity)
{
	P1SEL |= BIT5 + BIT6 + BIT7;
	P1SEL2 |= BIT5 + BIT6 + BIT7;
	P1DIR |= BIT5 + BIT6 + BIT7;
	UCB0CTL1 |= UCSWRST;
	UCB0CTL0 |= (((uint16_t)SPI_Phase_Polarity)<<6) + UCMSB + UCMST+ UCSYNC;
	UCB0CTL1 |= UCSSEL_2; // SMCLK
	UCB0BR1 = ((baudRate)&0xFF00)>>8;
	UCB0BR0 = (baudRate)&0xFF;
	UCB0CTL1 &= ~UCSWRST;
}

void initSPI(SERIAL_CLASSES * spiClass)
{
	switch(spiClass->module)
	{
	case MODULE_B:
		P1SEL |= BIT5 + BIT6 + BIT7;
		P1SEL2 |= BIT5 + BIT6 + BIT7;
		break;
	default:
		break;
	}

	UCB0CTL0 |=  UCCKPH +  UCMSB + UCMST + UCSYNC;
	UCB0CTL1 |= UCSSEL_2;

	switch(spiClass->baudRate)
	{
		case BAUD_MAX:
			UCB0BR0 |= 0x00; // MAX
			break;
		case SMCLK_16MHZ_SPI_CLK_4MHZ:
			UCB0BR0 |= 0x0A; // MAX
			break;
	}
	UCB0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
}

void clearRXHead()
{
	rx0Head = 0;
}

void initUSI(SERIAL_CLASSES * serialClass)
{
	switch(serialClass->serialType)
	{
		case UART:
			initUart(serialClass);
			break;
		case SPI:
			initSPI(serialClass);
		default:
			break;
	}
}

uint8_t writeReadByte(uint8_t data)
{
	uint8_t recv=0;
	UCB0TXBUF = data; // write INT to TX buffer
	while (!(IFG2 & UCB0TXIFG));
	while (UCB0STAT & UCBUSY);
	recv = UCB0RXBUF;
	return recv;

}

void writeStringTXD(char * data , SERIAL_CLASSES * serialClass)
{
	unsigned int i = 0;

	while(data[i])
	{
		switch(serialClass->module)
		{
		case MODULE_A:
			UCA0TXBUF = data[i];

			break;
		default:
			break;
		}
		while (!(IFG2 & UCA0TXIFG));
		while (UCA0STAT & UCBUSY);
		i++;
	}
}

void writeUartString(char * data)
{
	unsigned int i = 0;
	while(data[i])
	{
		UCA0TXBUF = data[i];
		while (!(IFG2 & UCA0TXIFG));
		while (UCA0STAT & UCBUSY);
		i++;
	}
}

uint8_t readUsiBuffer(SERIAL_CLASSES * serialClass, uint8_t * pBuf, uint8_t len)
{
	uint8_t cnt = 0;
	switch(serialClass->module)
	{
		case MODULE_A:
				while (len--)
				{
				  if (rx0Tail == rx0Head)
				  {
				    break;
				  }

				  *pBuf++ = rx0Buf[rx0Tail];
				  if (rx0Tail == 0)
				  {
					rx0Tail = UART_BUFFER_LEN-1;
				  }
				  else
				  {
				    rx0Tail--;
				  }
				  cnt++;
				}
			break;
		case MODULE_B:

			break;
		default:
			break;
	}
	return cnt;
}

uint8_t getReceivedLength()
{
	uint8_t size = 0;
	uint16_t localRxHead0 =rx0Head;
	uint16_t localRxTail0 = rx0Tail;
	if(localRxHead0 > localRxTail0 )
	{
		size = UART_BUFFER_LEN - localRxHead0 + localRxTail0;
	}
	else if(localRxHead0 < localRxTail0)
	{
		size = localRxTail0 - localRxHead0;
	}
	return size;
}


static const uint8_t AT_OKE[] = "[OK]";
static const uint8_t AT_ERROR[] = "[ERROR]";
volatile bool okBlockState = false;
volatile bool errorBlockState = false;

void resetOkBlockState()
{
	okBlockState = false;
}

bool getOkBlockState()
{
	return okBlockState;
}

void resetErrorBlockState()
{
	errorBlockState = false;
}

bool getErrorBlockState()
{
	return errorBlockState;
}


void lookForOK()
{
	static uint8_t okBlock = 0;
	if(rx0Buf[rx0Head]==AT_OKE[okBlock])
	{
		okBlock++;
	}
	else
	{
		okBlock=0;
	}
	if(okBlock>2)
	{
		okBlockState=true;
	}
}

void lookForError()
{
	static uint8_t errorBlock = 0;
	if(rx0Buf[rx0Head]==AT_ERROR[errorBlock])
	{
		errorBlock++;
	}
	else
	{
		errorBlock=0;
	}
	if(errorBlock>4)
	{
		errorBlockState=true;
	}
}

bool blockOnOk()
{
	volatile uint16_t retry=40;
	bool okFound=false;
	_delay_cycles(16000000);
	while(retry)
	{
		if(errorBlockState)
		{
			resetErrorBlockState();
			break;
		}
		else if(okBlockState==true)
		{
			resetOkBlockState();
			okFound=true;
			clearRXHead();
			break;
		}
		else
		{
			retry--;
			_delay_cycles(16000000);
		}
	}
	return okFound;
}

