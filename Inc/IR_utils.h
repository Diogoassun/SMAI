/*
 * IR_utils.h
 *
 *  Created on: July 14, 2025
 *      Author: lightry
 */

#ifndef IR_UTILS_H_
#define IR_UTILS_H_

#include <stdint.h>
#include <stdbool.h>

#define HEADERMARKHITACHIAC 3000
#define HEADERSPACEHITACHIAC 1650
#define ONEMARKHITACHIAC 500
#define ONESPACEMARKHITACHIAC 1050
#define ZEROMARKHITACHIAC 500
#define ZEROSPACEMARKHITACHIAC 325
#define FOOTERMARKHITACHIAC 500
#define GAPHITACHIAC 100000                     //Não utilizado quando não há repetição
#define MSB_FIRST_HITACHIAC false

void ir_send_generic(
    uint16_t headermark, uint32_t headerspace,
    uint16_t onemark, uint32_t onespace,
    uint16_t zeromark, uint32_t zerospace,
    uint16_t footermark, uint32_t gap,
    const uint8_t *data, uint16_t nbytes,
    bool msb_first, uint16_t repeat
);

void ir_send_hitachi_ac(const uint8_t *data, uint16_t nbytes, uint16_t repeat);

#endif /* IR_UTILS_H_ */
