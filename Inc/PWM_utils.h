/*
 * PWM_utils.h
 *
 *  Created on: July 14, 2025
 *      Author: lightry
 */
#ifndef PWM_UTILS_H_
#define PWM_UTILS_H_

#include "TIMER_registers.h"
#include "TIMER_utils.h"

void ir_init_pwm(void);
void ir_mark(uint32_t duration_us);
void ir_space(uint32_t duration_us);

#endif /* PWM_UTILS_H_ */
