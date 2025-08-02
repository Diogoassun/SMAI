/*
 * timer.c
 *
 *  Created on: Jun 1, 2025
 *      Author: leand
 */

#include "HW_types.h"
#include "TIMER_utils.h"
#include "RCC_utils.h"

void delay_ir_init(void){
    HW_REG(RCCA+RCC_APB1ENR) |= RCC_APB1ENR_TIM2EN_CLOCK_ENABLE; // Enable TIM2 clock
    HW_REG(TIMER2+TIMx_PSC) = 8 - 1;
    HW_REG(TIMER2+TIMx_ARR) = AUTO_RELOAD_VALUE; // auto-reload value
    HW_REG(TIMER2 + TIMx_EGR) = TIM_EGR_UG;
}

void delay_us_ir(unsigned short int us) {
    HW_REG(TIMER2+TIMx_CNT) = 0; // Reset the counter
    HW_REG(TIMER2+TIMx_CR1) |= TIM_CR1_CEN_SET; // Enable the timer
    while (HW_REG(TIMER2+TIMx_CNT) < us) {
        // Wait until the counter reaches the desired delay
    }
    HW_REG(TIMER2+TIMx_CR1) &= ~TIM_CR1_CEN_SET; // Disable the timer
}

/*

habilitar contador
*/

