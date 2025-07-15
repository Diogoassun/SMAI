/*
 * RTC_utils.h
 *
 *  Created on: Jun 1, 2025
 *      Author: leand
 */

#ifndef RTC_UTILS_H_
#define RTC_UTILS_H_

#include  "RTC_registers.h"

#define RTC_CRL_RTOFF	(1<<5)
#define RTC_CRL_CNF		(1<<4)
	#define ENTER_CONFIGURATION_MODE (1<<4)
#define RTC_CRL_RSF		(1<<3)

#define RCC_BDCR_RTCEN_MASK				(0x1<<15)
#define RCC_BDCR_RTCEN_RTC_CLOCK_ENABLE	(1<<15)

#define RCC_BDCR_RTCSEL_MASK			(0x3<<8)
#define RCC_BDCR_RTCSEL_LSE				(0x1<<8)
#define RCC_BDCR_RTCSEL_LSI				(0x2<<8)
#define RCC_BDCR_RTCSEL_HSE				(0x3<<8)

#define EXTI_IMR_MR17					(0x1<<17)
#define RTCAlarm_IRQ					(41)

#define RTC_CRH_ALRIE		(0x1<<1)
#define RTC_CRL_ALRF		(0x1<<1)

#define FREQ_32KHz			_32678_Hz_
#define FREQ_40KHz			_40000_Hz_
#define _32678_Hz_			0x7FFF
#define _40000_Hz_			0x9C3F

void __attribute__((weak)) rtc_init_config();
void __attribute__((weak)) rtc_set_config();

unsigned int __attribute__((weak)) rtc_get_time();

#endif /* RTC_UTILS_H_ */
