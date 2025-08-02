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

// --- Coolix timing em "ticks" de 276µs (≈10,5 ciclos a 38kHz) ---
#define kCoolixTick             276    // Approximately 10.5 cycles at 38kHz
#define kCoolixBitMarkTicks     2
#define kCoolixBitMark          (kCoolixBitMarkTicks * kCoolixTick)     // 552us
#define kCoolixOneSpaceTicks    6
#define kCoolixOneSpace         (kCoolixOneSpaceTicks * kCoolixTick)   // 1656us
#define kCoolixZeroSpaceTicks   2
#define kCoolixZeroSpace        (kCoolixZeroSpaceTicks * kCoolixTick)  // 552us
#define kCoolixHdrMarkTicks     17
#define kCoolixHdrMark          (kCoolixHdrMarkTicks * kCoolixTick)    // 4692us
#define kCoolixHdrSpaceTicks    16
#define kCoolixHdrSpace         (kCoolixHdrSpaceTicks * kCoolixTick)   // 4416us
#define kCoolixMinGapTicks      (kCoolixHdrMarkTicks + kCoolixZeroSpaceTicks)
#define kCoolixMinGap           (kCoolixMinGapTicks * kCoolixTick)     // 5244us
#define kCoolixExtraTolerance   5      // Percent

#define kDefaultMessageGap  100000U

//Hexas dos comandos do COOLIX - AC da sala
#define nBitsCoolix						24
#define LIGARAC23_COOLIX				0xB2BF50
#define DESLIGARAC_COOLIX				0xB27BE0
#define TEMPERATURA18_COOLIX			0xB2BF10
#define TEMPERATURA19_COOLIX			0xB2BF30
#define TEMPERATURA20_COOLIX			0xB2BF20
#define TEMPERATURA21_COOLIX			0xB2BF60
#define TEMPERATURA22_COOLIX			0xB2BF70
#define TEMPERATURA23_COOLIX			0xB2BF50
#define TEMPERATURA24_COOLIX			0xB2BF40
#define TEMPERATURA25_COOLIX			0xB2BFC0
#define TEMPERATURA26_COOLIX			0xB2BFD0
#define TEMPERATURA27_COOLIX			0xB2BF90
#define TEMPERATURA28_COOLIX			0xB2BF80
#define TEMPERATURA29_COOLIX	        0xB2BFA0
#define TEMPERATURA30_COOLIX			0xB2BFB0
#define MUDARDIRECAO_COOLIX				0xB20FE0
#define NREPEAT							1


void ir_send_generic(
    uint16_t headermark, uint32_t headerspace,
    uint16_t onemark, uint32_t onespace,
    uint16_t zeromark, uint32_t zerospace,
    uint16_t footermark, uint32_t gap,
    const uint8_t *data, uint16_t nbytes,
    bool msb_first, uint16_t repeat
);

void ir_send_hitachi_ac(const uint8_t *data, uint16_t nbytes, uint16_t repeat);
void ir_send_data(uint16_t onemark, uint32_t onespace, uint16_t zeromark,
                uint32_t zerospace, uint64_t data, uint16_t nbits,
                bool msb_first);

void ir_send_coolix(uint64_t data, uint16_t nbits, uint16_t repeat);

#endif /* IR_UTILS_H_ */
