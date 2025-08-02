/*
 * GPIO_utils.h
 *
 *  Created on: Jun 2, 2025
 *      Author: leand
 */

#ifndef GPIO_UTILS_H_
#define GPIO_UTILS_H_

#include "GPIO_registers.h"

#define GPIOx_CRLH_CNF_INPUT_ANALOG_MODE			(0b0000UL)
#define GPIOx_CRLH_CNF_INPUT_FLOATING				(0b0100UL)
#define GPIOx_CRLH_CNF_INPUT_PULL_UP_DOWN			(0b1000UL)

#define GPIOx_CRLH_CNF_OUTPUT_GP_PUSH_PULL			(0b0000UL)
#define GPIOx_CRLH_CNF_OUTPUT_GP_OPEN_DRAIN			(0b0100UL)
#define GPIOx_CRLH_CNF_OUTPUT_AF_PUSH_PULL			(0b1000UL)
#define GPIOx_CRLH_CNF_OUTPUT_AF_OPEN_DRAIN			(0b1100UL)

#define GPIOx_CRLH_MODE_INPUT				(0b00UL)
#define GPIOx_CRLH_MODE_10MHz				(0b01UL)
#define GPIOx_CRLH_MODE_2MHz				(0b10UL)
#define GPIOx_CRLH_MODE_50MHz				(0b11UL)

#define LCKK			(0x1<<16)
#define LCKR_MASK		(0xFFFF)

#define ATOMIC_SET_BIT_GPIO(gpiox, bit)	\
		HW_REG((gpiox)+GPIOx_BSRR) = (bit)

#define ATOMIC_CLEAR_BIT_GPIO(gpiox, bit)	\
		HW_REG((gpiox)+GPIOx_BRR) = (bit)

#define SET_BIT_GPIO(gpiox, pbitin)	\
		HW_REG((gpiox)+GPIOx_ODR) |= (bit)

#define CLEAR_BIT_GPIO(gpiox, bit)	\
		HW_REG((gpiox)+GPIOx_ODR) &= ~(bit)

#define TOGGLE_BIT_GPIO(gpiox, bit)	\
		HW_REG((gpiox)+GPIOx_ODR) ^= (bit)

void gpio_interrupt_config();
void __attribute__((weak)) gpio_init_config();
char __attribute__((weak)) lock_key_write_sequence(const short int port_bits);
void __attribute__((weak)) gpio_isr_callback();
void __attribute__((weak)) gpio_isr_nrfirq_callback();

#endif /* GPIO_UTILS_H_ */
