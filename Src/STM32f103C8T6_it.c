/*
 * STM32f103C8T6_it.c
 *
 *  Created on: May 19, 2025
 *      Author: leand
 */

#ifndef STM32F103C8T6_IT_C_
#define STM32F103C8T6_IT_C_

#include "EXTI_utils.h"
#include "HW_types.h"
#include "GPIO_registers.h"
#include "RTC_utils.h"
#include "DMA_utils.h"

void  __attribute__((weak)) RTCAlarm_IRQHandler(void){
	if (HW_REG(RTC+RTC_CRL) & RTC_CRL_ALRF){
		//HW_REG(GPIO_C+GPIOx_ODR) ^= (1<<13);	//Set C13
		//HW_REG(GPIO_C+GPIOx_BSRR) |= (1<<29);	//Set C13
		//for(volatile int i=0;i<100000;i++);

		//HW_REG(GPIO_C+GPIOx_BSRR) |= (1<<13);	//Reset C13
		//for(volatile int i=0;i<100000;i++);

		{
			while((HW_REG(RTC+RTC_CRL) & RTC_CRL_RTOFF) != RTC_CRL_RTOFF);
			HW_REG(RTC+RTC_CRL) |= (ENTER_CONFIGURATION_MODE); //To write RTC_PRL, RTC_CNT, RTC_ALR

			//HW_REG(RTC+RTC_CNTH) = 0;	//RW
			//HW_REG(RTC+RTC_CNTL) = 0;	//RW

			HW_REG(RTC+RTC_ALRH) = 0;	//Only Write
			HW_REG(RTC+RTC_ALRL) = HW_REG(RTC+RTC_ALRL) + 1;	//Only Write

			HW_REG(RTC+RTC_CRL) &= ~(ENTER_CONFIGURATION_MODE);
			while((HW_REG(RTC+RTC_CRL) & RTC_CRL_RTOFF) != RTC_CRL_RTOFF);
		}

		HW_REG(RTC+RTC_CRL) &= ~RTC_CRL_ALRF;
		HW_REG(EXTI+EXTI_PR) |= (1<<17);
		HW_REG(RTC+RTC_CRH) |= RTC_CRH_ALRIE;
	}
}

void __attribute__((weak)) SPI1_IRQHandler(void){

}

void __attribute__((weak)) DMA1_Channel2_IRQHandler(void){
	HW_REG(GPIO_C+GPIOx_ODR) ^= (1<<13);	//Toggle C13
	while(1){};
	if((HW_REG(DMA1+DMA_ISR)>>4) & DMA_ISR_HTIFx){
		HW_REG(DMA1+DMA_IFCR) &= DMA_IFCR_CHTIFx<<4;
	}
	if((HW_REG(DMA1+DMA_ISR)>>4) & DMA_ISR_TCIFx){
		HW_REG(DMA1+DMA_IFCR) &= DMA_IFCR_CTCIFx<<4;
	}
}

void DMA1_Channel3_IRQHandler(void){
	//HW_REG(GPIO_C+GPIOx_ODR) ^= (1<<13);	//Toggle C13
	if((HW_REG(DMA1+DMA_ISR)>>8) & DMA_ISR_HTIFx){
		HW_REG(DMA1+DMA_IFCR) |= DMA_IFCR_CHTIFx<<8;
	}
	if((HW_REG(DMA1+DMA_ISR)>>8) & DMA_ISR_TCIFx){
		HW_REG(DMA1+DMA_IFCR) |= DMA_IFCR_CTCIFx<<8;
	}
}

#endif /* STM32F103C8T6_IT_C_ */
