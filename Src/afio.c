/*
 * afio.c
 *
 *  Created on: Jun 20, 2025
 *      Author: leand
 */

#include "AFIO_utils.h"
#include "HW_types.h"
#include "RCC_utils.h"

#define PA							(0xF)
#define AFIO_EXTICR1_EXTI2			(PA << 8)

void afio_init_config(){
	ENABLE_CLOCK_APB2(RCC_APB2ENR_AFIOEN_CLOCK_ENABLE);
	//Set pin alternate function Remap default
	HW_REG(AFIO+AFIO_MAPR) &= ~AFIO_MAPR_SPI1_REMAP;
	HW_REG(AFIO+AFIO_MAPR) &= ~AFIO_MAPR_I2C1_REMAP;

	HW_REG(AFIO+AFIO_EXTICR1) &= ~AFIO_EXTICR1_EXTI2; // PA[2]
}

#undef AFIO_EXTICR1_EXTI2
#undef PA
