/*
 * I2C_utils.h
 *
 *  Created on: Jun 28, 2025
 *      Author: leand
 */

#ifndef I2C_UTILS_H_
#define I2C_UTILS_H_

#include "I2C_registers.h"

#define I2C_CR1_SWRST_UNDER_RESET				(0x1<<15)
#define I2C_CR1_ACK_ENABLE						(0x1<<10)
//#define I2C_CR1
#define I2C_CR1_STOP							(0x1<<9)
#define I2C_CR1_START							(0x1<<8)
#define I2C_CR1_PE_ENABLE						(0x1<<0)

#define I2C_SR1_TXE_EMPTY						(0x1<<7)
#define I2C_SR1_RXNE_NOT_EMPTY					(0x1<<6)
#define I2C_SR1_BTF_TRANSFER_SUCCEEDED			(0x1<<2)
#define I2C_SR1_ADDR_ADDRESS_MATCHED			(0x1<<1)
#define I2C_SR1_SB								(0x1<<0)

#define I2C_CR2_FREQ							(0x1F<<0)
#define I2C_CCR_FS_FAST_MODE_I2C				(0x1<<15)
#define I2C_CCR_CCR								(0xFFF<<0)
#define I2C_TRISE_TRISE							(0x3F)

void i2c_interrupt_config();
void i2c_dma_config();
void i2c_init_config();
void i2c_start();
void i2c_stop();
void i2c_set_address(unsigned char addr);
unsigned char i2c_transmit_data(unsigned char* tx_data, int size);
unsigned char i2c_receive_data(unsigned char address, unsigned char* rx_data, int size);

#endif /* I2C_UTILS_H_ */
