/*
 * SPI_utils.h
 *
 *  Created on: Jun 20, 2025
 *      Author: leand
 */

#ifndef SPI_UTILS_H_
#define SPI_UTILS_H_

#include "SPI_registers.h"

#define SPI_CR1_BIDIMODE_LINES_BIDIRECTIONAL		(0x1<<15)
#define SPI_CR1_CRCEN_CRC_ENABLE					(0x1<<13)
#define SPI_CR1_DFF_16BIT_DATA_FRAME				(0x1<<11)
#define SPI_CR1_RXONLY_RECEIVE_ONLY_MODE			(0x1<<10)
#define SPI_CR1_SSM_SW_MANAGEMENT_ENABLE			(0x1<<9)
#define SPI_CR1_SSI_ENABLE							(0x1<<8)
#define SPI_CR1_LSBFIRST_LSB						(0x1<<7)
#define SPI_CR1_SPE_ENABLE							(0x1<<6)
#define SPI_CR1_BR_F_DIV2							(0x7<<3)
#define SPI_CR1_BR_MASK								(0x7)
#define SPI_CR1_MSTR_MASTER_CONFIGURATION			(0x1<<2)
#define SPI_CR1_CPOL_IDLE_HIGH						(0x1<<1)
#define SPI_CR1_CPHA_SECOND_CLOCK_TRANSITION		(0x1<<0)

#define SPI_CR2_TXEIE_ENABLE						(0x1<<7)
#define SPI_CR2_RXNEIE_ENABLE						(0x1<<6)
#define SPI_CR2_ERRIE_ENABLE						(0x1<<5)
#define SPI_CR2_SSOE_ENABLE							(0x1<<2)
#define SPI_CR2_TXDMAEN_ENABLE						(0x1<<1)
#define SPI_CR2_RXDMAEN_ENABLE						(0x1<<0)

#define SPI_SR_BSY									(0x1<<7)
#define SPI_SR_TXE_TX_BUFFER_EMPTY					(0x1<<1)
#define SPI_SR_RXNE_RX_BUFFER_NOT_EMPTY				(0x1<<0)

#define SPI_CS_PORT			GPIO_A
#define SPI_CS_PIN			(0x1<<4)

#define SELECT_CS_PIN_SPI()		\
		ATOMIC_CLEAR_BIT_GPIO(SPI_CS_PORT, SPI_CS_PIN)

#define UNSELECT_CS_PIN_SPI()	\
		ATOMIC_SET_BIT_GPIO(SPI_CS_PORT, SPI_CS_PIN)

#define ENABLE_SPE_SPI()			\
		HW_REG(SPI1+SPI_CR1) |= SPI_CR1_SPE_ENABLE;

#define DISABLE_SPE_SPI()			\
		HW_REG(SPI1+SPI_CR1) &= ~SPI_CR1_SPE_ENABLE;


void spi_dma_config();
void spi_init_config();

unsigned char spi_transmit_data(unsigned char* tx_data, int size);

unsigned char spi_receive_data(unsigned char* rx_data, int size);

unsigned char spi_dma_transmit_data(unsigned char* tx_data, unsigned char* dummy, int size);

unsigned char spi_dma_receive_data(unsigned char* rx_data, unsigned char* dummy, int size);

#endif /* SPI_UTILS_H_ */
