/*
 * SYSTICK_utils.h
 *
 *  Created on: May 31, 2025
 *      Author: leand
 */

#ifndef SYSTICK_UTILS_H_
#define SYSTICK_UTILS_H_

#include "SYSTICK_registers.h"

#define STK_CTRL_COUNTFLAG      (0x1<<16)
#define STK_CTRL_CLKSOURCE      (0x1<<2)
#define STK_CTRL_TICKINT        (0x1<<1)
#define STK_CTRL_ENABLE         (0x1<<0)

#define STK_LOAD_RELOAD_MASK    (0x00FFFFFF)

#define STK_VAL_CURRENT_MASK    (0x00FFFFFF)

#define STK_CALIB_NOREF         (0x1<<31)
#define STK_CALIB_SKEW          (0x1<<30)
#define STK_CALIB_TENMS_MASK    (0x00FFFFFF)

#define MICROSECONDS(micro)                     (micro)
#define MICROSECONDS_TO_MILISECONDS(micro)      ((micro)*1000)

#define SYSTICK_EXCEPTION_ENABLE() \
			HW_REG(STK + STK_CTRL) |= STK_CTRL_TICKINT;

#define SYSTICK_EXCEPTION_DISABLE() \
			HW_REG(STK + STK_CTRL) &= ~STK_CTRL_TICKINT;

//extern volatile unsigned char g_systick_flag;

//void __attribute__((weak)) systick_init_config();
void __attribute__((weak)) systick_init_config(unsigned int ticks);
//void __attribute__((weak)) systick_reload_ticks(unsigned int ticks);
void systick_isr_callback();
unsigned char systick_countflag();
void systick_inc_tick(void);
unsigned long int systick_get_tick(void);
void systick_set_flag(void);
unsigned char systick_get_flag(void);
void systick_clear_flag(void);
unsigned int systick_get_timeout(void);
void systick_set_timeout(void);
void systick_clear_timeout(void);

#endif /* SYSTICK_UTILS_H_ */
