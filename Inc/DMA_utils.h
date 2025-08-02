/*
 * DMA_utils.h
 *
 *  Created on: Jun 25, 2025
 *      Author: leand
 */

#ifndef DMA_UTILS_H_
#define DMA_UTILS_H_

#include "DMA_registers.h"

#define DMA_CCRx_MEM2MEM_ENABLE				(0x1<<14)
#define DMA_CCRx_PL_MASK					(0x3<<12)
#define DMA_CCRx_PSIZE_MASK					(0x3<<10)
#define DMA_CCRx_MINC_ENABLE				(0x1<<7)
#define DMA_CCRx_PINC_ENABLE				(0x1<<6)
#define DMA_CCRx_CIRC_ENABLE				(0x1<<5)
#define DMA_CCRx_DIR_FROM_MEMORY			(0x1<<4)
#define DMA_CCRx_TEIE_INTERUPT_ENABLE		(0x1<<3)
#define DMA_CCRx_HTIE_INTERUPT_ENABLE		(0x1<<2)
#define DMA_CCRx_TCIE_INTERUPT_ENABLE		(0x1<<1)
#define DMA_CCRx_EN_CHANNEL_ENABLE			(0x1<<0)

#define DMA_ISR_TEIFx						(0x1<<3)
#define DMA_ISR_HTIFx						(0x1<<2)
#define DMA_ISR_TCIFx						(0x1<<1)
#define DMA_ISR_GIFx						(0x1<<0)

#define DMA_IFCR_CTEIFx						(0x1<<3)
#define DMA_IFCR_CHTIFx						(0x1<<2)
#define DMA_IFCR_CTCIFx						(0x1<<1)
#define DMA_IFCR_CGIFx						(0x1<<0)

#define DMA_CHANNEL1			0
#define DMA_CHANNEL2			1
#define DMA_CHANNEL3			2
#define DMA_CHANNEL4			3
#define DMA_CHANNEL5			4
#define DMA_CHANNEL6			5
#define DMA_CHANNEL7			6

void dma_init_config();
void dma_set_channel_config(unsigned char dmaa_channel, unsigned int peripheral_addr, unsigned int memory_addr, unsigned short int data_size);
void spi_transmit_dma(unsigned int peripheral_addr, unsigned int tx_data_memory_addr, unsigned int rx_data_memory_addr, unsigned short int data_size);
void spi_receive_dma(unsigned int peripheral_addr, unsigned int tx_data_memory_addr, unsigned int rx_data_memory_addr, unsigned short int data_size);

#endif /* DMA_UTILS_H_ */
