/*
 * EXTI_utils.h
 *
 *  Created on: Jun 2, 2025
 *      Author: leand
 */

#ifndef EXTI_UTILS_H_
#define EXTI_UTILS_H_

#include "EXTI_registers.h"

#define RTC_CRH_ALRIE		(0x1<<1)
#define RTC_CRL_ALRF		(0x1<<1)

#define RTC_CRL_RTOFF				(1<<5)
#define ENTER_CONFIGURATION_MODE	(1<<4)

void __attribute__((weak)) SysTick_Handler(void);

void EXTI0_IRQHandler(void);		/* EXTI Line0 interrupt                             */
void EXTI1_IRQHandler(void);		/* EXTI Line1 interrupt                             */
void EXTI2_IRQHandler(void);		/* EXTI Line2 interrupt                             */
void EXTI3_IRQHandler(void);		/* EXTI Line3 interrupt                             */
void EXTI4_IRQHandler(void);		/* EXTI Line4 interrupt                             */

void __attribute__((weak)) DMA1_Channel2_IRQHandler(void);
void __attribute__((weak)) DMA1_Channel3_IRQHandler(void);
void __attribute__((weak)) SPI1_IRQHandler(void);

void EXTI9_5_IRQHandler(void);		/* EXTI Line[9:5] interrupts                        */
void EXTI15_10_IRQHandler(void);	/* EXTI Line[15:10] interrupts                      */

void __attribute__((weak)) RTCAlarm_IRQHandler(void);

#endif /* EXTI_UTILS_H_ */
