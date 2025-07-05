/*
 * afio.c
 *
 *  Created on: Jun 20, 2025
 *      Author: leand
 */

#include "AFIO_utils.h"
#include "HW_types.h"
#include "RCC_utils.h"

void afio_init_config(){
	ENABLE_CLOCK_APB2(RCC_APB2ENR_AFIOEN_CLOCK_ENABLE);
	//Set pin alternate function Remap default
	HW_REG(AFIO+AFIO_MAPR) &= ~AFIO_MAPR_SPI1_REMAP;
	HW_REG(AFIO+AFIO_MAPR) &= ~AFIO_MAPR_I2C1_REMAP;
}
