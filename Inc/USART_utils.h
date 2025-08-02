/*
 * Usart_utils.h
 *
 *  Created on: Jul 15, 2025
 *      Author: ryanr
 */

#ifndef USART_UTILS_H_
#define USART_UTILS_H_

#include <stddef.h>
#include <string.h>
#include <stddef.h>
#include "stm32f1xx.h"

// protótipos
void usart1_clock_config(void);
void usart1_gpio_config(void);
void usart1_init_config(void);
void uart_write_int_ln(int value);
void uart_write(const char *s);
void process_command(const char *cmd);
void send_ir_command(uint8_t cmd_id);
void decrease_temperature();
void increase_temperature();

#define BUF_SIZE 64

#define TEMP_MIN_INDEX 0
#define TEMP_MAX_INDEX (sizeof(temp_codes)/sizeof(temp_codes[0]) - 1)

extern char rx_buffer[BUF_SIZE];
extern uint8_t rx_index;
extern uint8_t command_ready;
extern int current_temp_index;
extern const uint8_t temp_values[];
extern const uint32_t temp_codes[];


extern const char *commands[];

#endif /* USART_UTILS_H_ */
