/*
 * DEBUG.h
 *
 *  Created on: Jul 27, 2025
 *      Author: leand
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include "HW_types.h"

#define DBGMCU_CR			 		(0xE0042004)
#define DBGMCU_CR_DBG_WWDG_STOP		(0x1<<9)
#define DBGMCU_CR_DBG_IWDG_STOP		(0x1<<8)
#define DBGMCU_CR_DBG_STANDBY		(0x1<<2)
#define DBGMCU_CR_DBG_STOP			(0x1<<1)
#define DBGMCU_CR_DBG_SLEEP			(0x1<<0)


#define DEBUG_MODE_ON()	\
	HW_REG(DBGMCU_CR) |= DBGMCU_CR_DBG_STANDBY | DBGMCU_CR_DBG_STOP | DBGMCU_CR_DBG_SLEEP | DBGMCU_CR_DBG_IWDG_STOP;

#define DEBUG_MODE_OFF()	\
	HW_REG(DBGMCU_CR) &= ~(DBGMCU_CR_DBG_STANDBY | DBGMCU_CR_DBG_STOP | DBGMCU_CR_DBG_SLEEP | DBGMCU_CR_DBG_IWDG_STOP);

#endif /* DEBUG_H_ */
