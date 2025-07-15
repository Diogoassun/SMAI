/*
 * TIMER_registers.h
 *
 *  Created on: May 21, 2025
 *      Author: leand
 */

#ifndef TIMER_REGISTERS_H_
#define TIMER_REGISTERS_H_

#define TIMER1		0x40012C00UL
#define TIMER2		0x40000000UL
#define TIMER3		0x40000400UL
#define TIMER4		0x40000800UL
#define TIMER5		0x40000C00UL
#define TIMER6		0x40001000UL
#define TIMER7		0x40001400UL
#define TIMER8		0x40013400UL
#define TIMER9		0x40014C00UL
#define TIMER10		0x40015000UL
#define TIMER11		0x40015400UL
#define TIMER12		0x40001800UL
#define TIMER13		0x40001C00UL
#define TIMER14		0x40002000UL

//General-purpose registers
#define TIMx_CR1    (0x00)
#define TIMx_CR2    (0x04)
#define TIMx_SMCR   (0x08)
#define TIMx_DIER   (0x0C)
#define TIMx_SR     (0x10)
#define TIMx_EGR    (0x14)
#define TIMx_CCMR1  (0X18)
#define TIMx_CCMR2  (0X1C)
#define TIMx_CCER   (0x20)
#define TIMx_CNT    (0x24)
#define TIMx_PSC    (0x28)
#define TIMx_ARR    (0x2C)
#define TIMx_CCR1   (0x34)
#define TIMx_CCR2   (0x38)
#define TIMx_CCR3   (0x3C)
#define TIMx_CCR4   (0x40)
#define TIMx_BDTR   (0x44)
#define TIMx_DCR    (0x48)
#define TIMx_DMAR   (0x4C)

#endif /* TIMER_REGISTERS_H_ */
