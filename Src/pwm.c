/*
 * pwm.c
 *
 *  Created on: July 14, 2025
 *      Author: lightry
 */


#include "PWM_utils.h"
#include "HW_types.h"
#include "RCC_utils.h"

#define TIM_CCMR1_OC1M_set (0x7 << TIM_CCMR1_OC1M_Pos)
#define TIM_CCMR1_OC1M_PWM1 (0x6UL << TIM_CCMR1_OC1M_Pos) // PWM mode 1


void ir_init_pwm(void) {
    //enable tim1 clock
    ENABLE_CLOCK_APB2(RCC_APB2ENR_TIM1EN_CLOCK_ENABLE);

    // configure the timer for PWM in 38kHz
    HW_REG(TIMER1+TIMx_PSC) = 0; // prescaler
    HW_REG(TIMER1+TIMx_ARR) = 210;
    HW_REG(TIMER1+TIMx_CCR1) = 0; // initial duty cycle in 0%

    // configure pwm mode
    HW_REG(TIMER1+TIMx_CCMR1) &= ~TIM_CCMR1_OC1M_set; // clear OC1M bits
    HW_REG(TIMER1+TIMx_CCMR1) |= TIM_CCMR1_OC1M_PWM1; // set OC1M to PWM mode 1
    HW_REG(TIMER1+TIMx_CCMR1) |= TIM_CCMR1_OC1PE; // enable preload for CCR1

    /* ARPE + update generation */
    HW_REG(TIMER1+TIMx_CR1) |= TIM_CR1_ARPE; // ARPE bit
    HW_REG(TIMER1+TIMx_EGR) |= TIM_EGR_UG; // UG bit to generate an update event

    /* Habilita saída CH1 e inicia o timer principal (com controle principal) */
    HW_REG(TIMER1+TIMx_CCER) |= TIM_CCER_CC1E_SET; // enable output CH1

    /* Em TIM1 precisamos habilitar o “main output enable” */
    HW_REG(TIMER1+TIMx_BDTR) |= TIM_BDTR_MOE_SET; // MOE bit
    HW_REG(TIMER1+TIMx_CR1) |= TIM_CR1_CEN_SET; // enable the timer
}

void ir_mark(uint32_t duration_us){
    HW_REG(TIMER1+TIMx_CCR1) = HW_REG(TIMER1+TIMx_ARR) / 3; //Duty cycle of 33%
    delay_us_ir(duration_us);
    HW_REG(TIMER1+TIMx_CCR1) = 0; // Turn off the output
}

void ir_space(uint32_t duration_us){
   HW_REG(TIMER1+TIMx_CCR1) = 0; // Ensure the output is off
   delay_us_ir(duration_us);
}

