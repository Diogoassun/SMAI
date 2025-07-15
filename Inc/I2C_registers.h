/*
 * I2C_registers.h
 *
 *  Created on: Jun 28, 2025
 *      Author: leand
 */

#ifndef I2C_REGISTERS_H_
#define I2C_REGISTERS_H_

#define I2C1					(0x40005400UL)
//#define I2C2					(0x40005800UL)
#define I2C_CR1					(0x00)
#define I2C_CR2					(0x04)
#define I2C_OAR1				(0x08)
#define I2C_OAR2				(0x0C)
#define I2C_DR					(0x10)
#define I2C_SR1					(0x14)
#define I2C_SR2					(0x18)
#define I2C_CCR					(0x1C)
#define I2C_TRISE				(0x20)

#endif /* I2C_REGISTERS_H_ */
