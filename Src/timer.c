/*
 * timer.c
 *
 *  Created on: Jun 1, 2025
 *      Author: Juan Pablo
 */

#include "HW_types.h"
#include "TIMER_utils.h"

#define ENABLE_COUNTER_TIMER(base_addr)	\
		HW_REG(base_addr + TIMx_CR1) |= TIM_CR1_CEN;

#define STOP_COUNTER_TIMER(base_addr)	\
		HW_REG(base_addr + TIMx_CR1) &= ~TIM_CR1_CEN;

//interrupt flag General-purpose timers
#define SET_INTERRUPT_TIMER2 \
		HW_REG(TIMER2 + TIMx_DIER) = TIM_DIER_UIE;\
//		hw_regs(NVIC_ISER_0) |= TIM2_IRQ;
#define SET_INTERRUPT_TIMER3 \
		HW_REG(TIMER3 + TIMx_DIER) = TIM_DIER_UIE;\
//		hw_regs(NVIC_ISER_0) |= TIM3_IRQ;
#define SET_INTERRUPT_TIMER4 \
		HW_REG(TIMER4 + TIMx_DIER) = TIM_DIER_UIE;\
//		hw_regs(NVIC_ISER_0) |= TIM4_IRQ;
#define SET_INTERRUPT_TIMER5 \
		HW_REG(TIMER5 + TIMx_DIER) = TIM_DIER_UIE;\
//		hw_regs(NVIC_ISER_1) |= TIM5_IRQ;



void timer_set(unsigned int timer_base_addr, unsigned short int prescaler, unsigned int auto_reload_val){
	HW_REG(timer_base_addr + TIMx_PSC) = prescaler;
	HW_REG(timer_base_addr + TIMx_ARR) = auto_reload_val;
	HW_REG(timer_base_addr + TIMx_EGR)  = TIM_EGR_UG;
}

void timer_set_compare_mode(unsigned int timer_base_addr, unsigned char channel, unsigned char mode, unsigned char direction){
	unsigned int ccmr_offset, ccer_mask;
    unsigned char ocxm_shift, ccs_shift;
    switch (channel) {
        case 1:
            ccmr_offset = TIMx_CCMR1;
            ocxm_shift = 4;  // OC1M em CCMR1[6:4]
            ccs_shift = 0;   // CC1S em CCMR1[1:0]
            ccer_mask = 0x1; // CC1E em CCER[0]
            break;
        case 2:
            ccmr_offset = TIMx_CCMR1;
            ocxm_shift = 12; // OC2M em CCMR1[14:12]
            ccs_shift = 8;    // CC2S em CCMR1[9:8]
            ccer_mask = 0x10; // CC2E em CCER[4]
            break;
        case 3:
            ccmr_offset = TIMx_CCMR2;
            ocxm_shift = 4;  // OC3M em CCMR2[6:4]
            ccs_shift = 0;   // CC3S em CCMR2[1:0]
            ccer_mask = 0x100; // CC3E em CCER[8]
            break;
        case 4:
            ccmr_offset = TIMx_CCMR2;
            ocxm_shift = 12; // OC4M em CCMR2[14:12]
            ccs_shift = 8;   // CC4S em CCMR2[9:8]
            ccer_mask = 0x1000; // CC4E em CCER[12]
            break;
        default:
            return;
    }

    HW_REG(timer_base_addr + ccmr_offset) &= ~(0b11 << ccs_shift);
    HW_REG(timer_base_addr + ccmr_offset) |= (direction << ccs_shift);

    HW_REG(timer_base_addr + ccmr_offset) &= ~(0b111 << ocxm_shift);
    HW_REG(timer_base_addr + ccmr_offset) |= (mode << ocxm_shift);

    HW_REG(timer_base_addr + TIMx_CCER) |= ccer_mask;
}


void pwm_set(unsigned int timer_base_addr,unsigned short int prescaler, unsigned int period,unsigned int duty_cycle_percent, unsigned char channel, unsigned char mode){
	timer_set(timer_base_addr,prescaler,period);

	timer_set_compare_mode(timer_base_addr,channel,mode,0);

	unsigned int duty_cycle = (period * duty_cycle_percent) / 100;
    switch (channel) {
        case 1: HW_REG(timer_base_addr + TIMx_CCR1) = duty_cycle; break;
        case 2: HW_REG(timer_base_addr + TIMx_CCR2) = duty_cycle; break;
        case 3: HW_REG(timer_base_addr + TIMx_CCR3) = duty_cycle; break;
        case 4: HW_REG(timer_base_addr + TIMx_CCR4) = duty_cycle; break;
    }
    HW_REG(timer_base_addr + TIMx_CR1) |= TIM_CR1_ARPE;
    ENABLE_COUNTER_TIMER(timer_base_addr);
}
