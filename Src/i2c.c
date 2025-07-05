/*
 * i2c.c
 *
 *  Created on: Jun 28, 2025
 *      Author: leand
 */

#include "I2C_utils.h"
#include "HW_types.h"
#include "RCC_utils.h"

void i2c_interrupt_config(){
}

void i2c_dma_config(){
}

void i2c_init_config(){
	ENABLE_CLOCK_APB1(RCC_APB1ENR_I2C1EN_CLOCK_ENABLE);
	HW_REG(I2C1+I2C_CR1) |= I2C_CR1_SWRST_UNDER_RESET;
	HW_REG(I2C1+I2C_CR1) &= ~I2C_CR1_SWRST_UNDER_RESET;

	HW_REG(I2C1+I2C_CR2) &= ~I2C_CR2_FREQ;	// Set APB1 clock frequency
	HW_REG(I2C1+I2C_CR2) |= (8<<0);

	HW_REG(I2C1+I2C_CCR) &= ~I2C_CCR_FS_FAST_MODE_I2C;
	HW_REG(I2C1+I2C_CCR) &= ~I2C_CCR_CCR;
	// ((4*10^(-6)) + (1000*10^(-9)) )/(1/(8*10^6)) 40
	HW_REG(I2C1+I2C_CCR) |= (40<<0);	// ((4ms) + (1ms) )/(1/(8ms)) 40 Set clock control register for 100KHz in Standard mode

	HW_REG(I2C1+I2C_TRISE) &= ~I2C_TRISE_TRISE;
	// (1*10^(-6))/(1/(8*10^6)) + 1
	HW_REG(I2C1+I2C_TRISE) |= (9<<0);	// (1ms)/(1/(8ms)) + 1 Set maximum rise time

	HW_REG(I2C1+I2C_CR1) |= I2C_CR1_PE_ENABLE;
}

void i2c_start(){
	HW_REG(I2C1+I2C_CR1) |= I2C_CR1_START;
	while(!(HW_REG(I2C1+I2C_SR1) & I2C_SR1_SB)){};
}

void i2c_stop(){
	HW_REG(I2C1+I2C_CR1) |= I2C_CR1_STOP;
}

void i2c_set_address(unsigned char addr){
	HW_REG(I2C1+I2C_DR) &= ~(0x00FF);
	HW_REG(I2C1+I2C_DR) |= addr | 0x1;	// Write

	while(!(HW_REG(I2C1+I2C_SR1) & I2C_SR1_ADDR_ADDRESS_MATCHED)){};
	HW_REG(I2C1+I2C_SR1);
	HW_REG(I2C1+I2C_SR2);
}

unsigned char i2c_transmit_data(unsigned char* tx_data, int size){

	unsigned int i=0;
	for(;i<size;){
		// Enquanto o buffer estiver cheio
		while(!(HW_REG(I2C1+I2C_SR1) & I2C_SR1_TXE_EMPTY)){};
		HW_REG(I2C1+I2C_DR) &= ~(0x00FF);
		HW_REG(I2C1+I2C_DR) |= tx_data[i];
		++i;
	}
	while(!(HW_REG(I2C1+I2C_SR1) & I2C_SR1_BTF_TRANSFER_SUCCEEDED)){};

	return 1;
}


unsigned char i2c_receive_data(unsigned char address, unsigned char* rx_data, int size){
	int remaining = size;
	// STEP 1
	if (size == 1)
	{
		// STEP 1-a
		//HW_REG(I2C1+I2C_DR) &= ~(0x00FF);
		HW_REG(I2C1+I2C_DR) = address;  //  send the address
		while(!(HW_REG(I2C1+I2C_SR1) & I2C_SR1_ADDR_ADDRESS_MATCHED)){};  // wait for ADDR bit to set
		// STEP 1-b
		HW_REG(I2C1+I2C_CR1) &= ~I2C_CR1_ACK_ENABLE;
		unsigned char temp = HW_REG(I2C1+I2C_SR1) | HW_REG(I2C1+I2C_SR2);  // read SR1 and SR2 to clear the ADDR bit.... EV6 condition
		HW_REG(I2C1+I2C_CR1) |= I2C_CR1_STOP;  // Stop I2C
		// STEP 1-c
		while(!(HW_REG(I2C1+I2C_SR1) & I2C_SR1_RXNE_NOT_EMPTY)){}; // wait for RxNE to set
		// STEP 1-d
		rx_data[size-remaining] = HW_REG(I2C1+I2C_DR);  // Read the data from the DATA REGISTER
		remaining--;
	}
	// STEP 2
	else
	{
		// STEP 2-a
		//HW_REG(I2C1+I2C_DR) &= ~(0x00FF);
		HW_REG(I2C1+I2C_DR) = address;
		while(!(HW_REG(I2C1+I2C_SR1) & I2C_SR1_ADDR_ADDRESS_MATCHED)){};  // wait for ADDR bit to set
		// STEP 2-b
		unsigned char temp = HW_REG(I2C1+I2C_SR1) | HW_REG(I2C1+I2C_SR2);  // read SR1 and SR2 to clear the ADDR bit

		while (remaining>2)
		{
			// STEP 2-c
			while(!(HW_REG(I2C1+I2C_SR1) & I2C_SR1_RXNE_NOT_EMPTY)){}; // wait for RxNE to set
			// STEP 2-d
			rx_data[size-remaining] = HW_REG(I2C1+I2C_DR);  // Read the data from the DATA REGISTER
			// STEP 2-e
			HW_REG(I2C1+I2C_CR1) |= I2C_CR1_ACK_ENABLE;

			remaining--;
		}
		// Read the SECOND LAST BYTE
		while(!(HW_REG(I2C1+I2C_SR1) & I2C_SR1_RXNE_NOT_EMPTY)){}; // wait for RxNE to set
		rx_data[size-remaining] = HW_REG(I2C1+I2C_DR);

		// STEP 2-f
		HW_REG(I2C1+I2C_CR1) &= ~I2C_CR1_ACK_ENABLE;  // clear the ACK bit
		// STEP 2-g
		HW_REG(I2C1+I2C_CR1) |= I2C_CR1_STOP;  // Stop I2C

		// Read the Last BYTE
		while(!(HW_REG(I2C1+I2C_SR1) & I2C_SR1_RXNE_NOT_EMPTY)){}; // wait for RxNE to set
		rx_data[size-remaining] = HW_REG(I2C1+I2C_DR);  // copy the data into the buffer
		remaining--;
	}

	return 1;
}
