/*
 * systick.c
 *
 *  Created on: May 25, 2025
 *      Author: leand
 */

#include "HW_types.h"
#include "SYSTICK_utils.h"

volatile unsigned char g_systick_flag = 0;
static volatile unsigned long int g_systick_ticks = 0;
static volatile unsigned long int timeout = 0;



void systick_isr_callback(){
	g_systick_flag = 35;
}

void __attribute__((weak)) systick_init_config(unsigned int ticks){
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
    HW_REG(STK+STK_LOAD) = (ticks - 1) & STK_LOAD_RELOAD_MASK;
    //HW_REG(STK + STK_CTRL) = (STK_CTRL_CLKSOURCE | STK_CTRL_TICKINT | STK_CTRL_ENABLE);
    HW_REG(STK + STK_VAL) = 0;
    HW_REG(STK + STK_CTRL) &= ~STK_CTRL_CLKSOURCE;
    HW_REG(STK + STK_CTRL) |= (STK_CTRL_TICKINT | STK_CTRL_ENABLE);

    //NVIC_SetPriority(RTCAlarm_IRQ,0x10); // Priority level 1

    //NVIC_EnableIRQ(RTCAlarm_IRQ);	// Enable EXTI17 interrupt on NVIC
}

unsigned char systick_countflag(){
	return (HW_REG(STK + STK_CTRL) & STK_CTRL_COUNTFLAG)>>16;
}

void systick_inc_tick(void) {
	g_systick_ticks++;
}

unsigned long int systick_get_tick(void) {
	return g_systick_ticks;
}

void systick_set_flag(void)
{
    g_systick_flag = 1;
}

unsigned char systick_get_flag(void)
{
    return g_systick_flag;
}

void systick_clear_flag(void)
{
    g_systick_flag = 0;
}


unsigned int systick_get_timeout(void){
	return timeout;
}

void systick_set_timeout(){
	timeout = 1;
}

void systick_clear_timeout(){
	timeout = 0;
}
