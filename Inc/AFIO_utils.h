/*
 * AFIO_utils.h
 *
 *  Created on: Jun 20, 2025
 *      Author: leand
 */

#ifndef AFIO_UTILS_H_
#define AFIO_UTILS_H_

#include "AFIO_registers.h"

#define AFIO_MAPR_I2C1_REMAP		(0x1<<1)
#define AFIO_MAPR_SPI1_REMAP		(0x1<<0)

void afio_init_config();

#endif /* AFIO_UTILS_H_ */
