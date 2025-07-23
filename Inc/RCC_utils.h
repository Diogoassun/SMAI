/*
 * RCC_utils.h
 *
 *  Created on: Jun 1, 2025
 *      Author: leand
 */

#ifndef RCC_UTILS_H_
#define RCC_UTILS_H_

#include "RCC_registers.h"

//HSI oscillator clock, HSE oscillator clock, PLL clock
#define RCC_CR_PLLON_MASK				(1<<24)
#define RCC_CR_PLLON_ON					(1<<24)
#define RCC_CR_PLLRDY					(1<<25)

#define RCC_CR_HSEON_MASK				(1<<16)
#define RCC_CR_HSE_OSCILLATOR_ON		(1<<16)
#define RCC_CR_HSERDY					(1<<17)

#define RCC_CR_HSION_MASK				(1<<0)
#define RCC_CR_HSION_OSCILLATOR_ON		(1<<0)
#define RCC_CR_HSIRDY					(1<<1)

#define RCC_CFGR_PLLMUL_MASK						(0xF)
#define RCC_CFGR_PLLMUL_PLL_INPUT_CLOCKx4			((0x2 & RCC_CFGR_PLLMUL_MASK)<<18)

#define RCC_CFGR_PLLSRC_MASK						(0x1)
#define RCC_CFGR_PLLSRC_HSI_OSCILLATOR_CLOCK		((0x1 & RCC_CFGR_PLLSRC_MASK)<<16)

#define RCC_CFGR_HPRE_MASK				(0xF)
#define RCC_CFGR_HPRE_SYSCLK_NOT_DIV	((0xF & RCC_CFGR_HPRE_MASK)<<4)
#define RCC_CFGR_HPRE_SYSCLK_DIV4	((0b1001 & RCC_CFGR_HPRE_MASK)<<4)

#define RCC_CFGR_SWS_MASK				(0x3)
#define RCC_CFGR_SWS_HSI				((0x0 & RCC_CFGR_SW_MASK)<<2)
#define RCC_CFGR_SWS_HSE				((0x1 & RCC_CFGR_SW_MASK)<<2)
#define RCC_CFGR_SWS_PLL				((0x2 & RCC_CFGR_SW_MASK)<<2)

#define RCC_CFGR_SW_MASK				(0x3)
#define RCC_CFGR_SW_HSI					((0x0 & RCC_CFGR_SW_MASK)<<0)
#define RCC_CFGR_SW_HSE					((0x1 & RCC_CFGR_SW_MASK)<<0)
#define RCC_CFGR_SW_PLL					((0x2 & RCC_CFGR_SW_MASK)<<0)

#define RCC_CR_HSEON_OSCILLATOR_ON		(0x1<<16)

#define RCC_CSR_LSION_MASK				(0x1<<0)
#define RCC_CSR_LSION_OSCILLATOR_ON		(0x1<<0)
#define RCC_CSR_LSIRDY					(0x1<<1)

#define RCC_BDCR_LSE_MASK				(0x1<<0)
#define RCC_BDCR_LSEON_OSCILLATOR_ON	(0x1<<0)
#define RCC_BDCR_LSERDY					(0x1<<1)

#define RCC_PWREN_MASK					(0x1<<28)
#define RCC_PWREN_CLOCK_ENABLE			(0x1<<28)

#define RCC_BKPEN_MASK					(0x1<<27)
#define RCC_BKPEN_CLOCK_ENABLE			(0x1<<27)

#define RCC_AHBENR_DMA1EN_CLOCK_ENABLE		(1<<0)

#define RCC_APB1ENR_I2C2EN_CLOCK_ENABLE		(0x1<<22)
#define RCC_APB1ENR_I2C1EN_CLOCK_ENABLE		(0x1<<21)

#define RCC_APB2ENR_IOAEEN_CLOCK_ENABLE		(1<<2)
#define RCC_APB2ENR_IOBEEN_CLOCK_ENABLE		(1<<3)
#define RCC_APB2ENR_IOCEEN_CLOCK_ENABLE		(1<<4)

#define RCC_APB2ENR_SPI1EN_CLOCK_ENABLE		(0x1<<12)
#define RCC_APB2ENR_AFIOEN_CLOCK_ENABLE		(0x1<<0)

void __attribute__((weak)) system_clock_config();
void __attribute__((weak)) secondary_clock_config();

#define ENABLE_CLOCK_AHB(ahb) \
		HW_REG(RCCA+RCC_AHBENR) |= (ahb);

#define ENABLE_CLOCK_APB1(apb1) \
		HW_REG(RCCA+RCC_APB1ENR) |= (apb1);

#define ENABLE_CLOCK_APB2(apb2) \
		HW_REG(RCCA+RCC_APB2ENR) |= (apb2);


#endif /* RCC_UTILS_H_ */
