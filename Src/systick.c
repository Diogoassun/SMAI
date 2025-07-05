/*
 * systick.c
 *
 *  Created on: May 25, 2025
 *      Author: leand
 */

#include "HW_types.h"
#include "SYSTICK_utils.h"

void __attribute__((weak)) systick_init_config(){
/*
	HW_REG(RCCA+RCC_CFGR) & (0x3<<2);

	if(HSI){

	}

	if(PLL){

	}

	if(HSE){

	}

	HW_REG(STK+STK_LOAD) = MICROSECONDS_TO_MILISECONDS(1);
	HW_REG(STK+STK_VAL) &= ~STK_VAL_CURRENT_MASK;
	HW_REG(STK+STK_CALIB);

	HW_REG(STK+STK_CTRL) &= ~STK_CTRL_COUNTFLAG;
	HW_REG(STK+STK_CTRL) &= ~STK_CTRL_CLKSOURCE;
	HW_REG(STK+STK_CTRL) &= ~STK_CTRL_TICKINT;
	HW_REG(STK+STK_CTRL) |= STK_CTRL_ENABLE;
*/
}
