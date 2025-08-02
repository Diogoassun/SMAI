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
#include "GPIO_utils.h"
#include "RTC_utils.h"
#include "DMA_utils.h"
#include "SYSTICK_utils.h"

//volatile unsigned long int tg = 0;
extern volatile unsigned char g_dma_tx_complete;
extern volatile unsigned char g_dma_rx_complete;
extern volatile unsigned int state_listenig_timeout;

void __attribute__((weak)) SysTick_Handler(void)
{
	state_listenig_timeout = 1;
	//systick_set_timeout();
	//systick_isr_callback();
	//systick_set_flag();
	//tg=systick_get_tick();
	//systick_inc_tick();
}

/* EXTI Line0 interrupt                             */
void EXTI0_IRQHandler(void){

}

/* EXTI Line1 interrupt                             */
void EXTI1_IRQHandler(void){

}

/* EXTI Line2 interrupt                             */
void EXTI2_IRQHandler(void){
	gpio_isr_nrfirq_callback();
}

/* EXTI Line3 interrupt                             */
void EXTI3_IRQHandler(void){

}

/* EXTI Line4 interrupt                             */
void EXTI4_IRQHandler(void){

}

void __attribute__((weak)) DMA1_Channel2_IRQHandler(void){

	if((HW_REG(DMA1+DMA_ISR)>>4) & DMA_ISR_HTIFx){
		HW_REG(DMA1+DMA_IFCR) |= DMA_IFCR_CHTIFx<<4;
	}

	if((HW_REG(DMA1+DMA_ISR)>>4) & DMA_ISR_TCIFx){
		//HW_REG(GPIO_C+GPIOx_ODR) ^= (1<<13);	//Toggle C13
		//for(volatile int i = 0;i<200000;i++);

		g_dma_rx_complete = 1;

		//HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL2)) &= ~DMA_CCRx_EN_CHANNEL_ENABLE;	// RX

		HW_REG(DMA1+DMA_IFCR) |= DMA_IFCR_CTCIFx<<4;
	}
}

void __attribute__((weak)) DMA1_Channel3_IRQHandler(void){

	if((HW_REG(DMA1+DMA_ISR)>>8) & DMA_ISR_HTIFx){
		HW_REG(DMA1+DMA_IFCR) |= DMA_IFCR_CHTIFx<<8;
	}

	if((HW_REG(DMA1+DMA_ISR)>>8) & DMA_ISR_TCIFx){
		//HW_REG(GPIO_C+GPIOx_ODR) ^= (1<<13);	//Toggle C13
		//for(volatile int i = 0;i<200000;i++);
		g_dma_tx_complete = 1;

		//HW_REG(DMA1+DMA_CCRx(DMA_CHANNEL3)) &= ~DMA_CCRx_EN_CHANNEL_ENABLE;	// TX

		HW_REG(DMA1+DMA_IFCR) |= DMA_IFCR_CTCIFx<<8;
	}
}

void __attribute__((weak)) SPI1_IRQHandler(void){

}

/* EXTI Line[9:5] interrupts                        */
void EXTI9_5_IRQHandler(void){

}

/* EXTI Line[15:10] interrupts                      */
void EXTI15_10_IRQHandler(void){

}

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


#endif /* STM32F103C8T6_IT_C_ */
