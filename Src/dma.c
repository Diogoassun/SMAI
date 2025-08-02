/*
 * dma.c
 *
 *  Created on: Jun 24, 2025
 *      Author: leand
 */

#include "DMA_utils.h"
#include "HW_types.h"
#include "RCC_utils.h"
#include "stm32f1xx.h"

#define MEMORY_SIZE					(0x3<<10)
#define PERIPHERAL_SIZE				(0x3<<8)
#define CHANNEL_PRIORITY_LOW		(0x3<<12)

#define DMA1_Channel2_IRQ			(12)
#define DMA1_Channel3_IRQ			(13)

#define ENABLE_CHANNEL2_DMA()	\
		HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL2)) |= DMA_CCRx_EN_CHANNEL_ENABLE;

#define ENABLE_CHANNEL3_DMA()	\
		HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3)) |= DMA_CCRx_EN_CHANNEL_ENABLE;

#define DISABLE_CHANNEL2_DMA()	\
		HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL2)) &= ~DMA_CCRx_EN_CHANNEL_ENABLE;

#define DISABLE_CHANNEL3_DMA()	\
		HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3)) &= ~DMA_CCRx_EN_CHANNEL_ENABLE;

volatile unsigned char g_dma_tx_complete;
volatile unsigned char g_dma_rx_complete;

void dma_init_config(){
	ENABLE_CLOCK_AHB(RCC_AHBENR_DMA1EN_CLOCK_ENABLE);

	// SPI1_RX
	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL2));
	//HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL2)) |= DMA_CCRx_TEIE_INTERUPT_ENABLE;
	//HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL2)) |= DMA_CCRx_HTIE_INTERUPT_ENABLE;
	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL2)) |= DMA_CCRx_TCIE_INTERUPT_ENABLE;

	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL2)) &= ~DMA_CCRx_DIR_FROM_MEMORY;	//Read from peripheral

	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL2)) &= ~MEMORY_SIZE;	// 8 bits
	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL2)) &= ~PERIPHERAL_SIZE;

	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL2)) &= ~DMA_CCRx_MEM2MEM_ENABLE;
	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL2)) &= ~CHANNEL_PRIORITY_LOW;	// PL = 0

	//HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL2)) &= ~DMA_CCRx_MINC_ENABLE;
	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL2)) &= ~DMA_CCRx_PINC_ENABLE;
	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL2)) &= ~DMA_CCRx_CIRC_ENABLE;
	// SPI1_RX

	// SPI1_TX
	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3));
	//HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3)) |= DMA_CCRx_TEIE_INTERUPT_ENABLE;
	//HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3)) |= DMA_CCRx_HTIE_INTERUPT_ENABLE;
	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3)) |= DMA_CCRx_TCIE_INTERUPT_ENABLE;

	//HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3)) &= ~DMA_CCRx_DIR_FROM_MEMORY;	//Read from peripheral
	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3)) |= DMA_CCRx_DIR_FROM_MEMORY;	//Read from memory

	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3)) &= ~MEMORY_SIZE;
	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3)) &= ~PERIPHERAL_SIZE;

	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3)) &= ~DMA_CCRx_MEM2MEM_ENABLE;
	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3)) &= ~CHANNEL_PRIORITY_LOW;	// PL = 0

	//HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3)) |= DMA_CCRx_MINC_ENABLE;
	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3)) &= ~DMA_CCRx_PINC_ENABLE;
	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3)) &= ~DMA_CCRx_CIRC_ENABLE;
	// SPI1_RX

	NVIC_SetPriority(DMA1_Channel3_IRQ,0x10); // Priority level 1
	NVIC_SetPriority(DMA1_Channel2_IRQ,0x10); // Priority level 1

	NVIC_EnableIRQ(DMA1_Channel3_IRQ);	// Enable EXTI17 interrupt on NVIC
	NVIC_EnableIRQ(DMA1_Channel2_IRQ);	// Enable EXTI17 interrupt on NVIC

	__enable_irq();
}

void dma_set_channel_config(unsigned char dmaa_channel, unsigned int peripheral_addr, unsigned int memory_addr, unsigned short int data_size){
	HW_REG(DMA1+DMA_CCRx(dmaa_channel)) &= ~DMA_CCRx_EN_CHANNEL_ENABLE;

	//HW_REG(DMA1+DMA_CNDTRx(dmaa_channel)) &= ~0x0000FFFF;
	HW_REG(DMA1+DMA_CNDTRx(dmaa_channel)) = data_size;
	HW_REG(DMA1+DMA_CPARx(dmaa_channel)) = peripheral_addr;
	HW_REG(DMA1+DMA_CMARx(dmaa_channel)) = memory_addr;

	HW_REG(DMA1+DMA_CCRx(dmaa_channel)) |= DMA_CCRx_EN_CHANNEL_ENABLE;
}

void spi_transmit_dma(unsigned int peripheral_addr, unsigned int tx_data_memory_addr, unsigned int rx_data_memory_addr, unsigned short int data_size){
	g_dma_tx_complete = 0;

	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3)) &= ~DMA_CCRx_EN_CHANNEL_ENABLE;	// TX
	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL2)) &= ~DMA_CCRx_EN_CHANNEL_ENABLE;	// RX

	//HW_REG(DMA1+DMA_CNDTRx(dmaa_channel)) &= ~0x0000FFFF;
	HW_REG(DMA1+DMA_CNDTRx(DMA_CHANNEL3)) = data_size;
	HW_REG(DMA1+DMA_CPARx(DMA_CHANNEL3)) = peripheral_addr;
	HW_REG(DMA1+DMA_CMARx(DMA_CHANNEL3)) = tx_data_memory_addr;
	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3)) |= DMA_CCRx_MINC_ENABLE;	// Inc TX

	//HW_REG(DMA1+DMA_CNDTRx(dmaa_channel)) &= ~0x0000FFFF;
	HW_REG(DMA1+DMA_CNDTRx(DMA_CHANNEL2)) = data_size;
	HW_REG(DMA1+DMA_CPARx(DMA_CHANNEL2)) = peripheral_addr;
	HW_REG(DMA1+DMA_CMARx(DMA_CHANNEL2)) = rx_data_memory_addr;
	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL2)) &= ~DMA_CCRx_MINC_ENABLE;	// Fix RX

	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL2)) |= DMA_CCRx_EN_CHANNEL_ENABLE;	// Rx
	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3)) |= DMA_CCRx_EN_CHANNEL_ENABLE;	// TX

	while (g_dma_tx_complete == 0) {};
}

void spi_receive_dma(unsigned int peripheral_addr, unsigned int tx_data_memory_addr, unsigned int rx_data_memory_addr, unsigned short int data_size){
	g_dma_rx_complete = 0;

	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3)) &= ~DMA_CCRx_EN_CHANNEL_ENABLE;	// TX
	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL2)) &= ~DMA_CCRx_EN_CHANNEL_ENABLE;	// RX

	//HW_REG(DMA1+DMA_CNDTRx(dmaa_channel)) &= ~0x0000FFFF;
	HW_REG(DMA1+DMA_CNDTRx(DMA_CHANNEL3)) = data_size;
	HW_REG(DMA1+DMA_CPARx(DMA_CHANNEL3)) = peripheral_addr;
	HW_REG(DMA1+DMA_CMARx(DMA_CHANNEL3)) = tx_data_memory_addr;
	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3)) &= ~DMA_CCRx_MINC_ENABLE;	// Fix TX

	//HW_REG(DMA1+DMA_CNDTRx(dmaa_channel)) &= ~0x0000FFFF;
	HW_REG(DMA1+DMA_CNDTRx(DMA_CHANNEL2)) = data_size;
	HW_REG(DMA1+DMA_CPARx(DMA_CHANNEL2)) = peripheral_addr;
	HW_REG(DMA1+DMA_CMARx(DMA_CHANNEL2)) = rx_data_memory_addr;
	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL2)) |= DMA_CCRx_MINC_ENABLE;	// Inc Rx

	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL2)) |= DMA_CCRx_EN_CHANNEL_ENABLE;	// Rx
	HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3)) |= DMA_CCRx_EN_CHANNEL_ENABLE;	// TX

	while (g_dma_rx_complete == 0) {};
}
