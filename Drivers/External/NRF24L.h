/*
 * NRF24L.h
 *
 *  Created on: Mar 2, 2014
 *      Author: Nate
 */

#ifndef NRF24L_H_
#define NRF24L_H_

#include "stdint.h"
#include "stdbool.h"
#include "msp430g2553.h"

#ifndef NULL
    #define NULL ((void *)0)
#endif


/******************************************************************************
 * Global functions
 *****************************************************************************/

void initNRF24L(void);
void handleRxData();
void transmitTxData(uint8_t * data);
uint8_t getNrfStatus();
bool recievedRfData();
void getRfBuffer(uint8_t * buffer);
void handleTxData();


/*---------------- NRF24L  GPIO --------------------------- */

/* SPI Lines */
#define DEVIO_P1OUT_SCK			(0x01 << 5)
#define DEVIO_P1IN_MISO			(0x01 << 6)
#define DEVIO_P1OUT_MOSI		(0x01 << 7)

/* nRF24L SPI select line controls. */
#define NRF_SPI_ENABLE          (P2OUT &= ~DEVIO_P2OUT_NRF_CSN)
#define NRF_SPI_DISABLE         (P2OUT |= DEVIO_P2OUT_NRF_CSN)

/* nRF24L TX/RX power control lines. */
#define NRF_CE_HIGH             (P2OUT |= DEVIO_P2OUT_NRF_CE)
#define NRF_CE_LOW              (P2OUT &= ~DEVIO_P2OUT_NRF_CE)

/* nRF Module Control Lines */
#define DEVIO_NRF_IRQ 		(0x01 << 7)
#define NRF_IRQ_INPUT		(P3IN)
#define DEVIO_P2OUT_NRF_CSN 	(0x01 << 7)
#define DEVIO_P2OUT_NRF_CE 		(0x01 << 6)
#define XTAL_TO_GPIO	P2SEL &=~(BIT6+BIT7); P2SEL2 &=~(BIT6+BIT7)
/*------------------------------------------------------------ */


/* Dummy byte used to pad SPI clock cycles to get morz bytes!*/
#define DUMMY_BYTE 			0x00

/*--------------------------------- SPI Commands --------------------------- */
#define CMD_REG_READ 		0x00	// with 1-5 Data bytes
#define CMD_REG_WRITE 		0x20	// with 1-5 Data bytes
#define CMD_RX_READ			0x61	// with 1-32 Data bytes
#define CMD_TX_WRITE		0xA0	// with 1-32 Data bytes
#define CMD_TX_FLUSH		0xE1	// 0 data bytes
#define CMD_RX_FLUSH		0xE2	// 0 data bytes
#define CMD_NOP				0xFF	// 0 data bytes
/*------------------------------- NRF24L Memory map ------------------------ */

/*------------- Config register ------------ */
#define REG_CONFIG			0x00
#define	MASK_RX_DR			(1 << 6)	/* Mask RX interrupt */
#define	MASK_TX_DS			(1 << 5)	/* Mask TX interrupt */
#define MASK_MAX_RT			(1 << 4)	/* Mask MAX_RT interrupt */
#define EN_CRC				(1 << 3)	/* Enable CRC */
#define CRCO				(1 << 2)	/* CRC encoding scheme*/
/* '0' - 1 byte, '1' - 2 bytes */
#define PWR_UP				(1 << 1) 	/* Power up */
#define PRIM_RX				(1 << 0)	/* 1 - PRX, 0 - PTX*/
#define PRIM_TX             (0 << 0)

/*------ Enhanched Shockburst auto ack ----- */
#define REG_ENAA			0x01
#define ENAA_P5				(1 << 5)	/* Auto ack for data pipe # */
#define ENAA_P4				(1 << 4)
#define ENAA_P3				(1 << 3)
#define ENAA_P2				(1 << 2)
#define ENAA_P1				(1 << 1)
#define ENAA_P0				(1 << 0)

/*--------Enable data-pipe RX address -------*/
#define REG_EN_RXADDR		0x02
#define ERX_P5				(1 << 5)	/* Data pipe to enable */
#define ERX_P4				(1 << 4)
#define ERX_P3				(1 << 3)
#define ERX_P2				(1 << 2)
#define ERX_P1				(1 << 1)
#define ERX_P0				(1 << 0)

/*---------- Data pipe address width --------*/
#define REG_SETUP_AW		0x03
#define ADDR_WIDTH_3		0x01
#define ADDR_WIDTH_4		0x02
#define ADDR_WIDTH_5		0x03

/*--------- Automatic retransmission --------*/
#define REG_SETUP_RETR			0x04
/* See datasheet for usage. */

/*--------------- RF Channel ----------------*/
#define REG_RF_CHAN				0x05
/* Bits 0 - 6 define the channel*/

/*------------- RF Setup register -----------*/
#define REG_RF_SETUP			0x06
#define PLL_LOCK				(1 << 4) 	/* Force PLL lock signal */
#define RF_DR_1Mbps				(0 << 3)	/* Data rate*/
#define RF_DR_2Mbps				(1 << 3)

#define RF_PWR_n18dBm			(0x00 << 1)	/* RF Power levels */
#define RF_PWR_n12dBm			(0x01 << 1)
#define RF_PWR_n6dBm			(0x02 << 1)
#define RF_PWR_0dBm				(0x03 << 1)

#define LNA_HCURR				(1 << 0)	/* Setup LNA gain, see datasheet*/

/*-------------- Status Register ------------*/
#define REG_STATUS				0x07
#define RX_DR					(1 << 6) 	/* Data ready RX, write 1 to clear */
#define TX_DS					(1 << 5)	/* Data sent on TX when ACK is received. Write 1 to clear */
#define MAX_RT					(1 << 4)	/* Max number of TX retries reached. Write 1 to clear */
#define RX_P_NO_MASK			(0x07 << 1)	/* Mask for reading RX_P_NO, see data sheet. */
#define TX_FULL					(1 << 0)	/* TX FIFO full */

/*------------ OBSERVE TX Register ----------*/
#define REG_OBSERVE_TX			(0x08)
/* See data sheet*/

/*--------- Carrier Detect Register ---------*/
#define REG_CD					(0x09)
/* See data sheet*/

/*------------ Address registers ------------*/
#define REG_RX_ADDR_P0			(0x0A)	/* See data sheet for usage */
#define REG_RX_ADDR_P1			(0x0B)
#define REG_RX_ADDR_P2			(0x0C)
#define REG_RX_ADDR_P3			(0x0D)
#define REG_RX_ADDR_P4			(0x0E)
#define REG_RX_ADDR_P5			(0x0F)

#define REG_TX_ADDR				(0x10)

/*----------FIFO RX Status Registers---------*/
#define REG_RX_PW_P0			(0x11)	/* Number of bytes in the RX pipe*/
#define REG_RX_PW_P1			(0x12)	/* See data sheet for usage */
#define REG_RX_PW_P2			(0x13)
#define REG_RX_PW_P3			(0x14)
#define REG_RX_PW_P4			(0x15)
#define REG_RX_PW_P5			(0x16)

/*-----------FIFO Register statuses----------*/
#define REG_FIFO_STATUS			(0x17)
#define TX_REUSE				(1 << 6)	/* See data sheet */
#define TX_FIFO_FULL			(1 << 5)
#define TX_FIFO_EMPTY			(1 << 4)
#define RX_FIFO_FULL			(1 << 1)
#define RX_FIFO_EMPTY			(1 << 0)

#define NRF_RF_CHANNEL              40
#define NRF_TX_ADDR_WIDTH           5
#define PAYLOAD_WIDTH 5                     // size of an RX/TX payload.

/******************************************************************************
 * Global variables
 *****************************************************************************/

extern uint8_t NRF_TX_ADDR[NRF_TX_ADDR_WIDTH];





#endif /* NRF24L_H_ */
