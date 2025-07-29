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

void ir_send_data(uint16_t onemark, uint32_t onespace,
                  uint16_t zeromark, uint32_t zerospace,
                  uint64_t data,   uint16_t nbits,
                  bool msb_first) {
    // Se não há bits, nada a fazer
    if (nbits == 0) return;

    if (msb_first) {
        // Se pediram mais bits do que cabe em `data`, envie zeros até encaixar
        while (nbits > sizeof(data) * 8) {
            ir_mark(zeromark);
            ir_space(zerospace);
            nbits--;
        }
        // Agora envia os bits visíveis, MSB primeiro
        for (uint64_t mask = 1ULL << (nbits - 1); mask; mask >>= 1) {
            if (data & mask) {
                ir_mark(onemark);
                ir_space(onespace);
            } else {
                ir_mark(zeromark);
                ir_space(zerospace);
            }
        }
    } else {
        // LSB primeiro
        for (uint16_t i = 0; i < nbits; i++, data >>= 1) {
            if (data & 1) {
                ir_mark(onemark);
                ir_space(onespace);
            } else {
                ir_mark(zeromark);
                ir_space(zerospace);
            }
        }
    }
}


void ir_send_coolix(uint64_t data, uint16_t nbits, uint16_t repeat) {
  if (nbits % 8 != 0) return;  // nbits is required to be a multiple of 8.


  for (uint16_t r = 0; r <= repeat; r++) {
    // Header
    ir_mark(kCoolixHdrMark);
    ir_space(kCoolixHdrSpace);

    // Data
    //   Break data into byte segments, starting at the Most Significant
    //   Byte. Each byte then being sent normal, then followed inverted.
    for (uint16_t i = 8; i <= nbits; i += 8) {
      // Grab a bytes worth of data.
      uint8_t segment = (data >> (nbits - i)) & 0xFF;
      // Normal
      ir_send_data(kCoolixBitMark, kCoolixOneSpace,
               kCoolixBitMark, kCoolixZeroSpace,
               segment, 8, true);
      // Inverted.
      ir_send_data(kCoolixBitMark, kCoolixOneSpace,
               kCoolixBitMark, kCoolixZeroSpace,
               segment ^ 0xFF, 8, true);
    }

    // Footer
    ir_mark(kCoolixBitMark);
    ir_space(kCoolixMinGap);  // Pause before repeating
  }
  ir_space(kDefaultMessageGap);
}

