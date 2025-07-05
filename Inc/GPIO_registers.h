/*
 * GPIO_registers.h
 *
 *  Created on: May 17, 2025
 *      Author: leand
 */

#ifndef GPIO_REGISTERS_H_
#define GPIO_REGISTERS_H_

#define GPIO_A		0x40010800UL
#define GPIO_B		0x40010C00UL
#define GPIO_C		0x40011000UL
#define GPIO_D
#define GPIO_E
#define GPIO_F
#define GPIO_G

//#define GPIOx_CRx_MASK(port)	(0xF<<(port))
#define GPIOx_CRL	0x00UL
#define GPIOx_CRH	0x04UL
#define GPIOx_IDR	0x08UL
#define GPIOx_ODR	0x0CUL
#define GPIOx_BSRR	0x10UL
#define GPIOx_BRR	0x14UL
#define GPIOx_LCKR	0x18UL

#endif /* GPIO_REGISTERS_H_ */
