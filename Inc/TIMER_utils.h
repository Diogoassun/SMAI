/*
 * TIMER_utils.h
 *
 *  Created on: Jun 1, 2025
 *      Author: Juan Pablo
 */

#ifndef TIMER_UTILS_H_
#define TIMER_UTILS_H_

#include "TIMER_registers.h"

#define TIM_CR1_CEN         (1 << 0)
#define TIM_CR1_UDIS        (1 << 1)
#define TIM_CR1_URS         (1 << 2)
#define TIM_CR1_DIR         (1 << 4)
#define TIM_CR1_ARPE        (1 << 7)

#define TIM_DIER_UIE        (1 << 0)
#define TIM_EGR_UG          (1 << 0)

#define TIM_SR_UIF          (1 << 0)

//TIMER NVIC
#define TIM2_IRQ 			(1 << 28)
#define TIM3_IRQ 			(1 << 29)
#define TIM4_IRQ 			(1 << 30)
#define TIM5_IRQ 			(1 << 50)


#define COMPARER_CHANNEL1			1
#define COMPARER_CHANNEL2			2
#define COMPARER_CHANNEL3			3
#define COMPARER_CHANNEL4			4

#define COMPARE_MODE_FROZEN         (0b000)
#define COMPARE_MODE_ACTIVE         (0b001)
#define COMPARE_MODE_INACTIVE       (0b010)
#define COMPARE_MODE_TOGGLE         (0b011)
#define COMPARE_MODE_FORCE_INACTIVE (0b100)
#define COMPARE_MODE_FORCE_ACTIVE   (0b101)
#define COMPARE_MODE_PWM1           (0b110)
#define COMPARE_MODE_PWM2           (0b111)



#endif /* TIMER_UTILS_H_ */
