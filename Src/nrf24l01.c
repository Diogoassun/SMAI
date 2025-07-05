/*
 * nrf24l01.c
 *
 *  Created on: Jun 21, 2025
 *      Author: leand
 */

#include "NRF24/nrf24l01.h"
#include "HW_types.h"
#include "SPI_utils.h"
#include "GPIO_utils.h"

#define EN_RXADDR_ERX_P1_ENABLE				(0x1<<1)
#define CONFIG_PWR_UP_ENABLE				(0x1<<1)
#define CONFIG_PRIM_RX_PRX					(0x1<<0)
#define NRF24L01_FIFO_STATUS_TX_EMPTY		(0x1<<4)
#define NRF24L01_DISCONNECTED				(0x1<<3)

#define STATUS_RX_DR						(0x1<<6)
#define STATUS_RX_P_NO_MASK					(0x7)
#define STATUS_RX_P_NO						(0x1<<1)


#define NRF24_CE_PORT		GPIO_A
#define NRF24_CE_PIN		(0x1<<3)

#define CHANNEL				10

#define ADDRESS0
#define ADDRESS1
#define ADDRESS2
#define ADDRESS3
#define ADDRESS4
#define ADDRESS5

#define SELECT_CS_PIN_NRF()		SELECT_CS_PIN_SPI()

#define UNSELECT_CS_PIN_NRF()	UNSELECT_CS_PIN_SPI()

#define ENABLE_CE_PIN_NRF()	\
		ATOMIC_SET_BIT_GPIO(NRF24_CE_PORT, NRF24_CE_PIN)

#define DISABLE_CE_PIN_NRF()	\
		ATOMIC_CLEAR_BIT_GPIO(NRF24_CE_PORT, NRF24_CE_PIN)

void nrf24_write_reg(unsigned char reg, unsigned char tx_data){
	unsigned char buff[2];
	buff[0] = W_REGISTER | reg;
	buff[1] = tx_data;

	SELECT_CS_PIN_NRF();

	spi_transmit_data(buff, 2);	//No timeout

	UNSELECT_CS_PIN_NRF();
}

void nrf24_multiwrite_reg(unsigned char reg, unsigned char* tx_data, unsigned int size){
	unsigned char buff[2];
	buff[0] = W_REGISTER | reg;
	//buff[1] = tx_data;

	SELECT_CS_PIN_NRF();

	spi_transmit_data(buff, 1);	//No timeout
	spi_transmit_data(tx_data, size);	//No timeout

	UNSELECT_CS_PIN_NRF();
}

unsigned char nrf24_read_reg(unsigned char reg){
	unsigned char buff[1];
	buff[0] = R_REGISTER | reg;

	unsigned char rx_data = 0;
	SELECT_CS_PIN_NRF();

	spi_transmit_data(buff, 1);	//No timeout
	spi_receive_data(&rx_data, 1);	//No timeout

	UNSELECT_CS_PIN_NRF();

	return rx_data;
}

void nrf24_multiread_reg(unsigned char reg, unsigned char* rx_data, unsigned int size){
	unsigned char buff[1];
	buff[0] = R_REGISTER | reg;

	SELECT_CS_PIN_NRF();

	spi_transmit_data(buff, 1);	//No timeout
	spi_receive_data(rx_data, size);	//No timeout

	UNSELECT_CS_PIN_NRF();
}

void nrf24_sendcmd_reg(unsigned char cmd){
	SELECT_CS_PIN_NRF();

	spi_transmit_data(&cmd, 1);	//No timeout

	UNSELECT_CS_PIN_NRF();
}

void nrf24_init_config(){
	DISABLE_CE_PIN_NRF();

	// reset all
	nrf24_reset(0);

	nrf24_write_reg(NRF24L01_CONFIG, 0x00);
	nrf24_write_reg(NRF24L01_EN_AA, 0x00);
	nrf24_write_reg(NRF24L01_EN_RXADDR, 0x00);
	nrf24_write_reg(NRF24L01_SETUP_AW, 0x03);	//5 bytes TX/RX address
	nrf24_write_reg(NRF24L01_SETUP_RETR, 0x00);
	nrf24_write_reg(NRF24L01_RF_CH, 0x00);
	nrf24_write_reg(NRF24L01_RF_SETUP, 0x0E);	//data rate 2Mbps, power 0dBm,

	ENABLE_CE_PIN_NRF();
}

//set tx mode
void nrf24_tx_mode(unsigned char* address, unsigned char channel){
	DISABLE_CE_PIN_NRF();

	nrf24_write_reg(NRF24L01_RF_CH, channel);
	nrf24_multiwrite_reg(NRF24L01_TX_ADDR, address, 5);

	nrf24_write_reg(NRF24L01_CONFIG, nrf24_read_reg(NRF24L01_CONFIG) | CONFIG_PWR_UP_ENABLE);

	ENABLE_CE_PIN_NRF();
}

unsigned char nrf24_transmit(unsigned char* tx_data){
	unsigned char cmd = W_TX_PAYLOAD;

	SELECT_CS_PIN_NRF();

	// spi_transmit payload command
	spi_transmit_data(&cmd, 1);
	// spi_transmit Send payload
	spi_transmit_data(tx_data, 32);	// payload de 32 bytes

	UNSELECT_CS_PIN_NRF();

	//delay;
	for(volatile int i=0;i<100000;i++){};

	unsigned char fifo_status = nrf24_read_reg(NRF24L01_FIFO_STATUS);

	if((fifo_status & NRF24L01_FIFO_STATUS_TX_EMPTY) && !(fifo_status & NRF24L01_DISCONNECTED))
	{
		nrf24_sendcmd_reg(FLUSH_TX);
		//reset FIFO_STATUS
		//nrf24_write_reg(NRF24L01_FIFO_STATUS, 0x11);
		nrf24_reset (NRF24L01_FIFO_STATUS);
		return 1;
	}

	return 0;
}

//set rx mode
void nrf24_rx_mode(unsigned char* address, unsigned char channel){
	DISABLE_CE_PIN_NRF();
	nrf24_reset (NRF24L01_STATUS);
	nrf24_write_reg(NRF24L01_RF_CH, channel);
	nrf24_write_reg(NRF24L01_EN_RXADDR, nrf24_read_reg(NRF24L01_EN_RXADDR) | EN_RXADDR_ERX_P1_ENABLE);
	nrf24_multiwrite_reg(NRF24L01_RX_ADDR_P1, address, 5);
	//nrf24_write_reg(NRF24L01_RX_ADDR_P2, 0xFF);
	nrf24_write_reg(NRF24L01_RX_PW_P1, 32);	//payload de 32 bytes

	nrf24_write_reg(NRF24L01_CONFIG, nrf24_read_reg(NRF24L01_CONFIG) | CONFIG_PRIM_RX_PRX);
	nrf24_write_reg(NRF24L01_CONFIG, nrf24_read_reg(NRF24L01_CONFIG) | CONFIG_PWR_UP_ENABLE);

	ENABLE_CE_PIN_NRF();
}

unsigned char is_data_available(char pipenum){
	unsigned char fifo_status = nrf24_read_reg(NRF24L01_STATUS);
	if((fifo_status & STATUS_RX_DR) && (fifo_status & (pipenum<<1)))
	{
		nrf24_write_reg(NRF24L01_STATUS, STATUS_RX_DR);
		fifo_status = nrf24_read_reg(NRF24L01_STATUS);
		return 1;
	}
	return 0;
}

void nrf24_receive(unsigned char* tx_data){
	unsigned char cmd = R_RX_PAYLOAD;

	SELECT_CS_PIN_NRF();

	// spi_transmit payload command
	spi_transmit_data(&cmd, 1);
	// spi_transmit receive payload
	spi_receive_data(tx_data, 32);	// receive 32 bytes

	UNSELECT_CS_PIN_NRF();

	// delay
	for(volatile int i=0;i<100000;i++){};

	nrf24_sendcmd_reg(FLUSH_RX);
}

void nrf24_reset(unsigned int REG)
{
	if (REG == NRF24L01_STATUS)
	{
		nrf24_write_reg(NRF24L01_STATUS, 0x00);
	}

	else if (REG == NRF24L01_FIFO_STATUS)
	{
		nrf24_write_reg(NRF24L01_FIFO_STATUS, 0x11);
	}

	else {
	nrf24_write_reg(NRF24L01_CONFIG, 0x08);
	nrf24_write_reg(NRF24L01_EN_AA, 0x3F);
	nrf24_write_reg(NRF24L01_EN_RXADDR, 0x03);
	nrf24_write_reg(NRF24L01_SETUP_AW, 0x03);
	nrf24_write_reg(NRF24L01_SETUP_RETR, 0x03);
	nrf24_write_reg(NRF24L01_RF_CH, 0x02);
	nrf24_write_reg(NRF24L01_RF_SETUP, 0x0E);
	nrf24_write_reg(NRF24L01_STATUS, 0x00);
	nrf24_write_reg(NRF24L01_OBSERVE_TX, 0x00);
	nrf24_write_reg(NRF24L01_RPD, 0x00);
	unsigned char rx_addr_p0_def[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
	nrf24_multiwrite_reg(NRF24L01_RX_ADDR_P0, rx_addr_p0_def, 5);
	unsigned char rx_addr_p1_def[5] = {0xC2, 0xC2, 0xC2, 0xC2, 0xC2};
	nrf24_multiwrite_reg(NRF24L01_RX_ADDR_P1, rx_addr_p1_def, 5);
	nrf24_write_reg(NRF24L01_RX_ADDR_P2, 0xC3);
	nrf24_write_reg(NRF24L01_RX_ADDR_P3, 0xC4);
	nrf24_write_reg(NRF24L01_RX_ADDR_P4, 0xC5);
	nrf24_write_reg(NRF24L01_RX_ADDR_P5, 0xC6);
	unsigned char tx_addr_def[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
	nrf24_multiwrite_reg(NRF24L01_TX_ADDR, tx_addr_def, 5);
	nrf24_write_reg(NRF24L01_RX_PW_P0, 0);
	nrf24_write_reg(NRF24L01_RX_PW_P1, 0);
	nrf24_write_reg(NRF24L01_RX_PW_P2, 0);
	nrf24_write_reg(NRF24L01_RX_PW_P3, 0);
	nrf24_write_reg(NRF24L01_RX_PW_P4, 0);
	nrf24_write_reg(NRF24L01_RX_PW_P5, 0);
	nrf24_write_reg(NRF24L01_FIFO_STATUS, 0x11);
	nrf24_write_reg(NRF24L01_DYNPD, 0);
	nrf24_write_reg(NRF24L01_FEATURE, 0);
	}
}

//UNDEF
#undef NRF24_CS_PORT
#undef NRF24_CS_PIN
#undef NRF24_CE_PORT
#undef NRF24_CE_PIN
