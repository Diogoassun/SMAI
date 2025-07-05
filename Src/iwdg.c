/*
 * iwdg.c
 *
 *  Created on: Jun 2, 2025
 *      Author: leand
 */

#include "IWDG_utils.h"
#include "HW_types.h"

void __attribute__((weak)) watchdog_init_config(){
	HW_REG(IWDG+IWDG_KR) |= 0xCCCC;
	HW_REG(IWDG+IWDG_KR) |= 0x5555;
	HW_REG(IWDG+IWDG_PR) |= 0x3<<0;
	HW_REG(IWDG+IWDG_RLR) |= 0xFFF<<0;
}
