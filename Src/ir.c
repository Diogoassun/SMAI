/*
 * ir.c
 *
 *  Created on: July 14, 2025
 *      Author: lightry
 */


#include "IR_utils.h"
#include "TIMER_utils.h"
#include "HW_types.h"
#include "PWM_utils.h"

 void ir_send_generic(
    uint16_t headermark, uint32_t headerspace,
    uint16_t onemark, uint32_t onespace,
    uint16_t zeromark, uint32_t zerospace,
    uint16_t footermark, uint32_t gap,
    const uint8_t *data, uint16_t nbytes,
    bool msb_first, uint16_t repeat
) {
    for (uint16_t r = 0; r <= repeat; r++) {
        if (headermark) ir_mark(headermark);
        if (headerspace) ir_space(headerspace);

        for (uint16_t i = 0; i < nbytes; i++) {
            uint8_t byte = data[i];
            for (uint8_t j = 0; j < 8; j++) {
                bool bit = msb_first ? (byte & (1 << (7 - j))) : (byte & (1 << j));
                if (bit) {
                    ir_mark(onemark);
                    ir_space(onespace);
                } else {
                    ir_mark(zeromark);
                    ir_space(zerospace);
                }
            }
        }

        if (footermark) ir_mark(footermark);
        if (gap > 0 && r < repeat) ir_space(gap);
    }
}

void ir_send_hitachi_ac(const uint8_t *data, uint16_t nbytes, uint16_t repeat){
    ir_send_generic(
        HEADERMARKHITACHIAC, HEADERSPACEHITACHIAC,
        ONEMARKHITACHIAC, ONESPACEMARKHITACHIAC,
        ZEROMARKHITACHIAC, ZEROSPACEMARKHITACHIAC,
        FOOTERMARKHITACHIAC, GAPHITACHIAC,
        data, nbytes, MSB_FIRST_HITACHIAC, repeat
    );
}

