/*
 * systick.c
 *
 *  Created on: May 25, 2025
 *      Author: leand
 */

#include "HW_types.h"
#include "SYSTICK_utils.h"
#include <stdint.h>

volatile uint8_t g_systick_flag = 0;

void SysTick_Handler(void)
{
    g_systick_flag = 1;
}

void __attribute__((weak)) systick_init_config(uint32_t ticks){
    HW_REG(STK + STK_LOAD) = (ticks - 1) & STK_LOAD_RELOAD_MASK;
    HW_REG(STK + STK_VAL) = 0;
    HW_REG(STK + STK_CTRL) = (STK_CTRL_CLKSOURCE | STK_CTRL_TICKINT | STK_CTRL_ENABLE);
}

uint8_t systick_get_flag(void)
{
    return g_systick_flag;
}

void systick_clear_flag(void)
{
    g_systick_flag = 0;
}
