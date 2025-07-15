/*
 * TIMER_utils.h
 *
 *  Created on: Jun 1, 2025
 *      Author: leand
 */

#ifndef TIMER_UTILS_H_
#define TIMER_UTILS_H_

#include "TIMER_registers.h"
#include <stdint.h>
#include <stdbool.h>

#define TIM_CCMR1_OC1M_Pos                  (4U)
#define TIM_CCMR1_OC1PE                     (1 << 3) 
#define TIM_CR1_ARPE                        (1 << 7) 
#define TIM_EGR_UG                          (1 << 0) 
#define TIM_CCER_CC1E_SET                   (1 << 0) 
#define TIM_BDTR_MOE_SET                    (1 << 15) 
#define TIM_CR1_CEN_SET                     (1 << 0) 
#define AUTO_RELOAD_VALUE                   0xFFFF 

void delay_us_ir(uint16_t us);
void delay_ir_init(void);

#endif /* TIMER_UTILS_H_ */
