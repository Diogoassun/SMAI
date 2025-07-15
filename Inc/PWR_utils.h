/*
 * PWR_utils.h
 *
 *  Created on: Jun 1, 2025
 *      Author: leand
 */

#ifndef PWR_UTILS_H_
#define PWR_UTILS_H_

#include "PWR_registers.h"

#define PWR_CR_DBP			(0x1<<8)
#define PWR_CR_PLS			(0x7<5)
#define PWR_CR_PVDE			(0x1<<4)
#define PWR_CR_CSBF			(0x1<<3)
#define PWR_CR_CWUF			(0x1<<2)
#define PWR_CR_PDDS			(0x1<<1)
#define PWR_CR_LPDS			(0x1<<0)

#define PWR_CSR_EWUP_MASK	(0x1)
#define PWR_CSR_EWUP		(1<<8)
#define PWR_CSR_PVDO_MASK	(0x1)
#define PWR_CSR_PVDO		(1<<2)
#define PWR_CSR_SBF_MAKS	(0x1)
#define PWR_CSR_SBF			(1<<1)
#define PWR_CSR_WUF_MASK	(0x1)
#define PWR_CSR_WUF			(1<<0)

#endif /* PWR_UTILS_H_ */
