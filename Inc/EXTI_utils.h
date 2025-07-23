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

void __attribute__((weak)) RTCAlarm_IRQHandler(void);
void __attribute__((weak)) SPI1_IRQHandler(void);
void __attribute__((weak)) DMA1_Channel2_IRQHandler(void);
void __attribute__((weak)) DMA1_Channel3_IRQHandler(void);

#endif /* EXTI_UTILS_H_ */
