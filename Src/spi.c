/*
 * spi.c
 *
 *  Created on: Jun 19, 2025
 *      Author: leand
 */

#include "SPI_utils.h"
#include "HW_types.h"
#include "stm32f1xx.h"
#include "RCC_utils.h"
#include "GPIO_utils.h"

#include "DMA_utils.h"

#define USE_SPI_DMA

#define SPI1_IRQ					(35)

void spi_interrupt_config(){
	HW_REG(SPI1+SPI_CR2) |= SPI_CR2_RXNEIE_ENABLE;	//RX full
	HW_REG(SPI1+SPI_CR2) |= SPI_CR2_TXEIE_ENABLE;	//TX empty
	HW_REG(SPI1+SPI_CR2) |= SPI_CR2_ERRIE_ENABLE;	//err

	NVIC_SetPriority(SPI1_IRQ,0x10); // Priority level 1

	NVIC_EnableIRQ(SPI1_IRQ);	// Enable EXTI17 interrupt on NVIC
}
void spi_dma_config(){
	HW_REG(SPI1+SPI_CR2) |= SPI_CR2_TXDMAEN_ENABLE;
	HW_REG(SPI1+SPI_CR2) |= SPI_CR2_RXDMAEN_ENABLE;
}

void spi_init_config(){
	ENABLE_CLOCK_APB2(RCC_APB2ENR_SPI1EN_CLOCK_ENABLE);
	//Disable SPI
	//HW_REG(SPI1+SPI_CR1) &= ~SPI_CR1_SPE_ENABLE;

	//HW_REG(SPI1+SPI_CR1) = 0;

	HW_REG(SPI1+SPI_CR1) &= ~SPI_CR1_BIDIMODE_LINES_BIDIRECTIONAL;	// Bimode 0
	HW_REG(SPI1+SPI_CR1) &= ~SPI_CR1_CRCEN_CRC_ENABLE;
	HW_REG(SPI1+SPI_CR1) &= ~SPI_CR1_RXONLY_RECEIVE_ONLY_MODE;		// Select full-duplex
	//HW_REG(SPI1+SPI_CR1) &= ~SPI_CR1_SSM_SW_MANAGEMENT_ENABLE;	// HARDWARE slave
	HW_REG(SPI1+SPI_CR1) |= SPI_CR1_SSM_SW_MANAGEMENT_ENABLE;		// Software slave
	HW_REG(SPI1+SPI_CR1) |= SPI_CR1_SSI_ENABLE;		// SSI enable

	// SPI clock frequency max 18 MHz
	HW_REG(SPI1+SPI_CR1) &= ~SPI_CR1_BR_F_DIV2;	// sysclk 8Mhz, div2 = 4MHz
	HW_REG(SPI1+SPI_CR1) &= ~SPI_CR1_CPOL_IDLE_HIGH;				// idle low
	HW_REG(SPI1+SPI_CR1) &= ~SPI_CR1_CPHA_SECOND_CLOCK_TRANSITION;	// low transition
	HW_REG(SPI1+SPI_CR1) &= ~SPI_CR1_DFF_16BIT_DATA_FRAME;			// 8bit data frame
	HW_REG(SPI1+SPI_CR1) &= ~SPI_CR1_LSBFIRST_LSB;					// MSB first

	//HW_REG(SPI1+SPI_CR2) |= SPI_CR2_SSOE_ENABLE;	//HARDWARE SLAVE

	HW_REG(SPI1+SPI_CR1) |= SPI_CR1_MSTR_MASTER_CONFIGURATION;		// select master

	HW_REG(SPI1+SPI_CR2) = 0;
	//Enable SPI
	//HW_REG(SPI1+SPI_CR1) |= SPI_CR1_SPE_ENABLE;	//Software slave
}

unsigned char spi_transmit_data(unsigned char* tx_data, int size){
#ifdef USE_SPI_DMA
	unsigned char dummy_rx_buffer;
	spi_transmit_dma(SPI1+SPI_DR, (unsigned int)tx_data, (unsigned int)&dummy_rx_buffer, size);
	return 0;
#else
	//HW_REG(SPI1+SPI_CR1) &= ~SPI_CR1_SSI_ENABLE;	//Software slave
	//HW_REG(SPI1+SPI_CR1) |= SPI_CR1_SPE_ENABLE;	//HARDWARE slave

	//HW_REG(SPI1+SPI_DR) = (short int) tx_data << 0;
	//while((HW_REG(SPI1+SPI_SR) & SPI_SR_BSY) || !(HW_REG(SPI1+SPI_SR) & SPI_SR_RXNE_RX_BUFFER_NOT_EMPTY)){};
	unsigned int i=0;
	for(;i<size;){
		// Enquanto o buffer estiver cheio
		while(!(HW_REG(SPI1+SPI_SR) & SPI_SR_TXE_TX_BUFFER_EMPTY)){};
		HW_REG(SPI1+SPI_DR) = tx_data[i];
		//miso = HW_REG(SPI1+SPI_DR);
		++i;
	}

	while(!(HW_REG(SPI1+SPI_SR) & SPI_SR_TXE_TX_BUFFER_EMPTY)){};
	while(HW_REG(SPI1+SPI_SR) & SPI_SR_BSY){};

	//HW_REG(SPI1+SPI_CR1) &= ~SPI_CR1_SPE_ENABLE;	//HARDWARE slave
	//HW_REG(SPI1+SPI_CR1) |= SPI_CR1_SSI_ENABLE;	//Software slave
	HW_REG(SPI1+SPI_DR);
	return (unsigned char)(HW_REG(SPI1+SPI_SR));
#endif
}


unsigned char spi_receive_data(unsigned char* rx_data, int size){
#ifdef USE_SPI_DMA
	unsigned char dummy_tx_buffer = 0;
	spi_receive_dma(SPI1+SPI_DR, (unsigned int)&dummy_tx_buffer, (unsigned int)rx_data, size);
#else
	unsigned int i=0;
	for(;i<size;){
		// Enquanto estiver em comunicação
		while(HW_REG(SPI1+SPI_SR) & SPI_SR_BSY){};
		HW_REG(SPI1+SPI_DR) = 0;	// dummy data
		// Espera por uma resposta
		while(!(HW_REG(SPI1+SPI_SR) & SPI_SR_RXNE_RX_BUFFER_NOT_EMPTY)){};
		rx_data[i] = (unsigned char)(HW_REG(SPI1+SPI_DR));
		++i;
	}

	while(!(HW_REG(SPI1+SPI_SR) & SPI_SR_TXE_TX_BUFFER_EMPTY)){};
	while(HW_REG(SPI1+SPI_SR) & SPI_SR_BSY){};
#endif
	return 0;
}

unsigned char spi_dma_transmit_data(unsigned char* tx_data, unsigned char* dummy, int size){
	//dma_set_channel_config(DMA_CHANNEL3, SPI1+SPI_DR, tx_data, size);
	spi_transmit_dma(SPI1+SPI_DR, (unsigned int)tx_data, (unsigned int)dummy, size);
	return 0;
}

unsigned char spi_dma_receive_data(unsigned char* rx_data, unsigned char* dummy, int size){
	//dma_set_channel_config(DMA_CHANNEL2, SPI1+SPI_DR, rx_data, size);
	spi_receive_dma(SPI1+SPI_DR, (unsigned int)dummy, (unsigned int)rx_data, size);
	return 0;
}
