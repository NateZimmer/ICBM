/*
 * NRF24L.c
 *
 *  Created on: Mar 2, 2014
 *      Author: Nate
 */

#include "NRF24L.h"
#include "../usi.h"

uint8_t NRF_TX_ADDR[NRF_TX_ADDR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};
static uint8_t retBuf[PAYLOAD_WIDTH];
static bool rfDataRecieved = false;

///////////////SPI INTERFACE LAYER///////////////////////

uint8_t SPI_SendCommand(uint8_t command, uint8_t data)
{
    uint8_t ret = 0;
    NRF_SPI_ENABLE;
    SLOW2_SPI;
    writeReadByte(command);
    ret = writeReadByte(data);
    NRF_SPI_DISABLE;
    FAST_SPI;
    return ret;
}

void SPI_SendBuffer(uint8_t command, uint8_t* buffer, uint8_t length, uint8_t* ret)
{
    uint8_t i = 0;
    uint8_t retByte = 0;
    SLOW2_SPI;
    NRF_SPI_ENABLE;
    retByte = writeReadByte(command); // Send first byte, the command
    if(ret != NULL)
    {
        ret[0] = retByte;
    }

    for(i = 0; i < length; i++)     // Send buffer
    {
        retByte = writeReadByte(buffer[i]);
        if(ret != NULL)
        {
            ret[i +1] = retByte;
        }
    }
    NRF_SPI_DISABLE;
    FAST_SPI;
}

void SPI_GetBuffer(uint8_t command, uint8_t* ret, uint8_t num_bytes)
{
    uint8_t i;

    NRF_SPI_ENABLE;
    SLOW2_SPI;
    (void) writeReadByte(command);

    for(i = 0; i < num_bytes; i++)
    {
       ret[i] = writeReadByte(DUMMY_BYTE);
    }
    NRF_SPI_DISABLE;
    FAST_SPI;
}

uint8_t SPI_SendByte(uint8_t data)
{
    uint8_t ret = 0 ;
    SLOW2_SPI;
    NRF_SPI_ENABLE;
    ret = writeReadByte(data);
    NRF_SPI_DISABLE;
    FAST_SPI;
    return ret;
}

/////////////////////////////////////////////////////////

void initNRF24L(void)
{
	/* Port 2 Directions */
	//P2SEL = 0x00; // For now, just set all pins to digital IO.
	XTAL_TO_GPIO;
	P2DIR |= DEVIO_P2OUT_NRF_CSN;
	P2DIR |= DEVIO_P2OUT_NRF_CE;
	P3DIR &= ~(DEVIO_NRF_IRQ);
	_delay_cycles(10000);

    NRF_CE_LOW;
    // Write TX address to TX address register
    SPI_SendBuffer( CMD_REG_WRITE + REG_TX_ADDR, NRF_TX_ADDR,
                    NRF_TX_ADDR_WIDTH, NULL);
    // Write TX address to data pipe 0 address register, ignore return data
    SPI_SendBuffer( CMD_REG_WRITE + REG_RX_ADDR_P0, NRF_TX_ADDR,
                    NRF_TX_ADDR_WIDTH, NULL);
    // Enable auto ack on data pipe 0
    SPI_SendCommand(CMD_REG_WRITE + REG_ENAA, ENAA_P0);
    // Enable data pipe 0
    SPI_SendCommand(CMD_REG_WRITE + REG_EN_RXADDR, ERX_P0);
    // Set the retry rate, Wait 500+86uS (0x10) and 10 retries (0x0A)
    SPI_SendCommand(CMD_REG_WRITE + REG_SETUP_RETR, 0x10 + 0x0A);
    // Set the RF channel
    SPI_SendCommand(CMD_REG_WRITE + REG_RF_CHAN, NRF_RF_CHANNEL);
    // Set the payload width for receiving
    SPI_SendCommand(CMD_REG_WRITE + REG_RX_PW_P0, PAYLOAD_WIDTH);
    // Set power and speed
    SPI_SendCommand(CMD_REG_WRITE + REG_RF_SETUP,
                    RF_PWR_0dBm + RF_DR_2Mbps + LNA_HCURR);
    // Clear out status flags, clear buffers
    SPI_SendCommand(CMD_REG_WRITE + REG_STATUS, MAX_RT + RX_DR + TX_DS);
    SPI_SendByte(CMD_TX_FLUSH);
    SPI_SendByte(CMD_RX_FLUSH);
    // Power up, primary receiver, CRC encoding - 2 bytes
    SPI_SendCommand(CMD_REG_WRITE + REG_CONFIG,
                    PRIM_RX + PWR_UP + EN_CRC + CRCO);
    NRF_CE_HIGH;
    _delay_cycles(10000);

}

void handleRxData()
{
	uint8_t ret= 0;
	if(!(DEVIO_NRF_IRQ & NRF_IRQ_INPUT))
	{
		ret = SPI_SendCommand(CMD_REG_READ + REG_STATUS, DUMMY_BYTE);
        	if (ret & RX_DR)
			{
				// Data was received, read payload, clear interrupt flag, check for more data
				do
				{
					SPI_GetBuffer(CMD_RX_READ, retBuf, PAYLOAD_WIDTH);
					SPI_SendCommand(CMD_REG_WRITE + REG_STATUS, RX_DR);
					ret = SPI_SendCommand(CMD_REG_READ + REG_FIFO_STATUS, DUMMY_BYTE);
				} while (!(ret & RX_FIFO_EMPTY));
				rfDataRecieved = true;
			}
	}
}

void handleTxData()
{
	uint8_t ret= 0;
	if(!(DEVIO_NRF_IRQ & NRF_IRQ_INPUT))
	{
		ret = SPI_SendCommand(CMD_REG_READ + REG_STATUS, DUMMY_BYTE);
        if(ret & TX_DS)
        {
            // TX was acknowledged, clear interrupt flag, set back to PRX
            SPI_SendCommand(CMD_REG_WRITE + REG_STATUS, TX_DS);
            NRF_CE_LOW;
			SPI_SendCommand(CMD_REG_WRITE + REG_CONFIG,PRIM_RX + PWR_UP + EN_CRC + CRCO);
			NRF_CE_HIGH;
        }
        else if (ret & MAX_RT)
        {
            // Maximum number of TX retries reached, clear flags, set back to PRX
            NRF_CE_LOW;
            SPI_SendCommand(CMD_REG_WRITE + REG_STATUS, MAX_RT);
            SPI_SendByte(CMD_TX_FLUSH);
            NRF_CE_LOW;
			SPI_SendCommand(CMD_REG_WRITE + REG_CONFIG,PRIM_RX + PWR_UP + EN_CRC + CRCO);
			NRF_CE_HIGH;
        }
	}
}

void transmitTxData(uint8_t * data)
{
    NRF_CE_LOW;
    SPI_SendBuffer( CMD_TX_WRITE, data, PAYLOAD_WIDTH, NULL);
    // Power up, primary transmitter, CRC encoding - 2 bytes
    SPI_SendCommand(CMD_REG_WRITE + REG_CONFIG,PRIM_TX + PWR_UP + EN_CRC + CRCO);
    NRF_CE_HIGH;
}

uint8_t getNrfStatus()
{
	uint8_t ret= 0;
    ret = SPI_SendCommand(CMD_REG_READ + REG_STATUS, DUMMY_BYTE);
    return ret;
}

bool recievedRfData()
{
	return rfDataRecieved;
}

void getRfBuffer(uint8_t * buffer)
{
	uint8_t index = 0;
	for(index = 0; index < PAYLOAD_WIDTH; index++)
	{
		buffer[index] = retBuf[index];
	}
	rfDataRecieved = false;
}



