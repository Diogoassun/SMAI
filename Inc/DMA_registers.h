/*
 * DMA_registers.h
 *
 *  Created on: Jun 24, 2025
 *      Author: leand
 */

#ifndef DMA_REGISTERS_H_
#define DMA_REGISTERS_H_

#define DMA1					(0x40020000UL)
#define DMA_ISR					(0x00)
#define DMA_IFCR				(0x04)
#define DMA_CCRx(channel)		(0x08 + 0x14 *(channel))
#define DMA_CNDTRx(channel)		(0x0C + 0x14 *(channel))
#define	DMA_CPARx(channel)		(0x10 + 0x14 *(channel))
#define	DMA_CMARx(channel)		(0x14 + 0x14 *(channel))

#endif /* DMA_REGISTERS_H_ */
