/*
 * SPI_registers.h
 *
 *  Created on: Jun 19, 2025
 *      Author: leand
 */

#ifndef SPI_REGISTERS_H_
#define SPI_REGISTERS_H_

#define SPI1			(0x40013000UL)
#define SPI_CR1			(0x00UL)
#define SPI_CR2			(0x04UL)
#define SPI_SR			(0x08UL)
#define SPI_DR			(0x0CUL)
#define SPI_CRCPR		(0x10UL)
#define SPI_RXCRCR		(0x14UL)
#define SPI_TXCRCR		(0x18UL)

#define SPI_I2SCFGR		(0x1CUL)
#define SPI_I2SPR		(0x20UL)

#endif /* SPI_REGISTERS_H_ */
