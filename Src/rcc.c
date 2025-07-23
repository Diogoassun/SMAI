/*
 * rcc.c
 *
 *  Created on: Jun 1, 2025
 *      Author: leand
 */

#include "HW_types.h"
#include "RCC_utils.h"
#include "PWR_utils.h"

typedef struct{
	int hsi;
	int lsi;
	int hse;
	int lse;
	int pplclk;	// 72MHz max
	int sysclk;	// 72MHz max
	int ahp;
	int apb1;	// 35MHz max
	int apb2;	// 72MHz max
}all_clock_typedef;

void __attribute__((weak)) system_clock_config(){
	/*
	HW_REG(RCCA+RCC_CR) |= RCC_CR_HSION_OSCILLATOR_ON;
	while((HW_REG(RCCA+RCC_CR) & RCC_CR_HSIRDY)!= RCC_CR_HSIRDY);

	HW_REG(RCCA+RCC_CFGR) |= RCC_CFGR_SW_HSI;
	while((HW_REG(RCCA+RCC_CFGR) & RCC_CFGR_SWS_HSE) != RCC_CFGR_SWS_HSI);
	*/

	//HW_REG(RCCA+RCC_CR) |= RCC_CR_HSION_OSCILLATOR_ON;
	//while((HW_REG(RCCA+RCC_CR) & RCC_CR_HSIRDY) != RCC_CR_HSIRDY);

	//HW_REG(RCCA+RCC_CR) |= RCC_CR_PLLON_ON;
	//while((HW_REG(RCCA+RCC_CR) & RCC_CR_PLLRDY) != RCC_CR_PLLRDY);

	//8MHz
	//HW_REG(RCCA+RCC_CFGR) &= ~RCC_CFGR_PLLSRC_HSI_OSCILLATOR_CLOCK;	//PLL entry clock source
	//4MHz
	//HW_REG(RCCA+RCC_CFGR) |= RCC_CFGR_PLLMUL_PLL_INPUT_CLOCKx4;	//PLL multiplication factor
	//16MHZ
	//HW_REG(RCCA+RCC_CFGR) &= ~RCC_CFGR_HPRE_SYSCLK_NOT_DIV;
	//HW_REG(RCCA+RCC_CFGR) |= RCC_CFGR_HPRE_SYSCLK_DIV4;	//SYSCLK divided by 4
	//4MHz

	//HW_REG(RCCA+RCC_CFGR) |= RCC_CFGR_SW_PLL;
	//while((HW_REG(RCCA+RCC_CFGR) & RCC_CFGR_SWS_PLL) != RCC_CFGR_SWS_PLL);
}

void __attribute__((weak)) secondary_clock_config(){
	HW_REG(RCCA+RCC_APB1ENR) |= RCC_PWREN_CLOCK_ENABLE;
	HW_REG(RCCA+RCC_APB1ENR) |= RCC_BKPEN_CLOCK_ENABLE;

	HW_REG(PWR + PWR_CR) |= PWR_CR_DBP;
	HW_REG(RCCA + RCC_BDCR) |= (1<<16);
	HW_REG(RCCA + RCC_BDCR) &= ~(1<<16);

	HW_REG(RCCA+RCC_CSR) |= RCC_CSR_LSION_OSCILLATOR_ON;
	while((HW_REG(RCCA+RCC_CSR) & RCC_CSR_LSIRDY) != RCC_CSR_LSIRDY);

	//HW_REG(RCCA+RCC_BDCR) |= RCC_BDCR_LSEON_OSCILLATOR_ON;
	//while((HW_REG(RCCA+RCC_BDCR) & RCC_BDCR_LSERDY) != RCC_BDCR_LSERDY);
}

