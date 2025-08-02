/*
 * rtc.c
 *
 *  Created on: Jun 1, 2025
 *      Author: leand
 */

#include "RTC_utils.h"
#include "HW_types.h"
#include "stm32f1xx.h"
#include "RCC_utils.h"
#include "EXTI_utils.h"

void __attribute__((weak)) rtc_init_config();
void __attribute__((weak)) rtc_set_config();

unsigned int __attribute__((weak)) rtc_get_time() {
	unsigned int high1 = HW_REG(RTC+RTC_CNTH);
	unsigned int low = HW_REG(RTC+RTC_CNTL);
	unsigned int high2 = HW_REG(RTC+RTC_CNTH);
    if (high1 != high2) {
        low = HW_REG(RTC+RTC_CNTL);
        high1 = high2;
    }
    return (high1 << 16) | low;
}

void rtc_init_config(){
	//HW_REG(RCCA+RCC_APB1ENR) |= RCC_PWREN_CLOCK_ENABLE;
	//HW_REG(RCCA+RCC_APB1ENR) |= RCC_BKPEN_CLOCK_ENABLE;

	//HW_REG(PWR + PWR_CR) |= PWR_CR_DBP;
	//HW_REG(RCCA + RCC_BDCR) |= (1<<16);

	HW_REG(RCCA+RCC_BDCR) |= RCC_BDCR_RTCSEL_LSI;
	HW_REG(RCCA+RCC_BDCR) |= RCC_BDCR_RTCEN_RTC_CLOCK_ENABLE;
	//HW_REG(RCCA+RCC_CSR) &= ~RCC_CSR_LSION_OSCILLATOR_ON;

	HW_REG(EXTI+EXTI_RTSR) |= EXTI_IMR_MR17;

	HW_REG(EXTI+EXTI_IMR) |= EXTI_IMR_MR17;

	//HW_REG(EXTI+EXTI_FTSR) |= EXTI_IMR_MR17;


	//HW_REG(PWR+PWR_CSR) |= PWR_CSR_EWUP;

	NVIC_SetPriority(RTCAlarm_IRQ,0x10); // Priority level 1

	NVIC_EnableIRQ(RTCAlarm_IRQ);	// Enable EXTI17 interrupt on NVIC

	__enable_irq();
}

void rtc_set_config(){
	//HW_REG(PWR + PWR_CR) |= PWR_CR_DBP;
	HW_REG(RTC+RTC_CRL) &= ~RTC_CRL_RSF; //Clear RSF
	while((HW_REG(RTC+RTC_CRL) & RTC_CRL_RSF) != RTC_CRL_RSF);

	while((HW_REG(RTC+RTC_CRL) & RTC_CRL_RTOFF) != RTC_CRL_RTOFF);
	HW_REG(RTC+RTC_CRL) |= (ENTER_CONFIGURATION_MODE); //To write RTC_PRL, RTC_CNT, RTC_ALR



	//HW_REG(RTC+RTC_PRLH) = 0;	//Only write
	//HW_REG(RTC+RTC_PRLL) = ((FREQ_40KHz+1)/2)-1;	//Only write
	HW_REG(RTC+RTC_PRLL) = FREQ_40KHz;	//Only write

	//HW_REG(RTC+RTC_DIVH);	//Only read
	//HW_REG(RTC+RTC_DIVL);	//Only read

	//HW_REG(RTC+RTC_CNTH) = 0;	//RW
	//HW_REG(RTC+RTC_CNTL) = 0;	//RW

	HW_REG(RTC+RTC_ALRH) = 0;	//Only Write
	HW_REG(RTC+RTC_ALRL) = HW_REG(RTC+RTC_ALRL) + 1;	//Only Write

	HW_REG(RTC+RTC_CRL) &= ~(ENTER_CONFIGURATION_MODE);
	while((HW_REG(RTC+RTC_CRL) & RTC_CRL_RTOFF) != RTC_CRL_RTOFF);

	HW_REG(RTC+RTC_CRL) &= ~RTC_CRL_ALRF;
	HW_REG(EXTI+EXTI_PR) |= (1<<17);
	HW_REG(RTC+RTC_CRH) |= RTC_CRH_ALRIE;	//RW active or not interrupt

	HW_REG(RTC+RTC_CRL) &= ~RTC_CRL_RSF; //Clear RSF
	//HW_REG(PWR + PWR_CR) &= ~PWR_CR_DBP;
	while((HW_REG(RTC+RTC_CRL) & RTC_CRL_RSF) != RTC_CRL_RSF);
}
