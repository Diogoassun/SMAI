/*
 * nrf24l01.h
 *
 *  Created on: Jun 21, 2025
 *      Author: leand
 */

#ifndef NRF24_NRF24L01_H_
#define NRF24_NRF24L01_H_

#include "NRF24/NRF24L01_registers.h"

void nrf24_init_config();

void nrf24_write_reg(unsigned char reg, unsigned char tx_data);

void nrf24_multiwrite_reg(unsigned char reg, unsigned char* tx_data, unsigned int size);

unsigned char nrf24_read_reg(unsigned char reg);

void nrf24_multiread_reg(unsigned char reg, unsigned char* rx_data, unsigned int size);

void nrf24_sendcmd_reg(unsigned char cmd);


void nrf24_tx_mode(unsigned char* address, unsigned char channel);
unsigned char nrf24_transmit(unsigned char* tx_data);

void nrf24_rx_mode(unsigned char* address, unsigned char channel);
unsigned char is_data_available(char pipenum);
void nrf24_receive(unsigned char* tx_data);
void nrf24_reset(unsigned int REG);

#endif /* NRF24_NRF24L01_H_ */
