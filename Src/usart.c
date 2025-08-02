/*
 * usart.c
 *
 *  Created on: Jul 15, 2025
 *      Author: ryanr
 */

#include "USART_utils.h"

#include "IR_utils.h"
#include "HW_types.h"

// Base
#define GPIO_A_BASE     0x40010800
#define RCC_BASE        0x40021000
#define USART1_BASE     0x40013800

// Offsets
#define GPIO_CRH_OFFSET 0x04
#define RCC_APB2ENR     0x18
#define USART_SR        0x00
#define USART_DR        0x04
#define USART_BRR       0x08
#define USART_CR1       0x0C

// Bits
#define USART1EN            (1 << 14)
#define IOPAEN              (1 << 2)
#define USART_RXNEIE        (1 << 5)
#define USART_RE            (1 << 2)
#define USART_TE            (1 << 3)
#define USART_UE            (1 << 13)
#define USART_TXE           (1 << 7)
#define USART_RXNE          (1 << 5)

#define CPU_CLK             8000000UL
#define BAUD_RATE           115200UL
#define BUF_SIZE            64

#define HW_REG8(x)  (*((volatile uint8_t *)(x)))

char rx_buffer[BUF_SIZE];
uint8_t rx_index = 0;
uint8_t command_ready = 0;

const char *commands[] = {
    "onac",
    "offac",
	"temp18",
	"temp19",
	"temp20",
	"temp21",
	"temp22",
    "temp23",
	"temp24",
	"temp25",
	"temp26",
	"temp27",
	"temp28",
	"temp29",
	"temp30",
	"ven",
	"mais",
	"menos",
    NULL
};

// Vetor com os códigos IR em ordem crescente de temperatura
const uint32_t temp_codes[] = {
    TEMPERATURA18_COOLIX,
    TEMPERATURA19_COOLIX,
    TEMPERATURA20_COOLIX,
    TEMPERATURA21_COOLIX,
    TEMPERATURA22_COOLIX,
    TEMPERATURA23_COOLIX,
    TEMPERATURA24_COOLIX,
    TEMPERATURA25_COOLIX,
    TEMPERATURA26_COOLIX,
    TEMPERATURA27_COOLIX,
    TEMPERATURA28_COOLIX,
    TEMPERATURA29_COOLIX,
    TEMPERATURA30_COOLIX
};

// Temperaturas correspondentes para log
const uint8_t temp_values[] = {
    18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30
};

int current_temp_index = 5;  // índice da temperatura 23°C



void usart1_clock_config(void) {
    HW_REG(RCC_BASE + RCC_APB2ENR) |= IOPAEN | USART1EN;
}

void usart1_gpio_config(void) {
    // PA9 TX AF‑PP
    HW_REG(GPIO_A_BASE + GPIO_CRH_OFFSET) &= ~(0xF << 4);
    HW_REG(GPIO_A_BASE + GPIO_CRH_OFFSET) |=  (0xB << 4);
    // PA10 RX input floating
    HW_REG(GPIO_A_BASE + GPIO_CRH_OFFSET) &= ~(0xF << 8);
    HW_REG(GPIO_A_BASE + GPIO_CRH_OFFSET) |=  (0x4 << 8);
}

void usart1_init_config(void) {
    // divisor de baud
    HW_REG(USART1_BASE + USART_BRR) = (CPU_CLK + BAUD_RATE/2) / BAUD_RATE;
    // habilita RX, TX, RXNEIE e USART
    HW_REG(USART1_BASE + USART_CR1) = USART_RE | USART_TE | USART_RXNEIE | USART_UE;
    NVIC_EnableIRQ(37);
}

void uart_write(const char *s) {
    while (*s) {
        while (!(HW_REG(USART1_BASE + USART_SR) & USART_TXE)) {}
        HW_REG8(USART1_BASE + USART_DR) = *s++;
    }
}

// ISR de recepção
void USART1_IRQHandler(void) {
    if (HW_REG(USART1_BASE + USART_SR) & USART_RXNE) {
        char c = HW_REG8(USART1_BASE + USART_DR);
        if (c != '\n' && c != '\r' && rx_index < BUF_SIZE-1) {
            rx_buffer[rx_index++] = c;
        } else {
            rx_buffer[rx_index] = '\0';
            rx_index = 0;
            command_ready = 1;
        }
    }
}

void uart_write_int_ln(int value) {
    char buffer[16];
    sprintf(buffer, "%d\r\n", value);
    uart_write(buffer);
}

void increase_temperature() {
    if (current_temp_index < TEMP_MAX_INDEX) {
        current_temp_index++;
        uart_write("Aumentando temperatura para ");
        uart_write_int_ln(temp_values[current_temp_index]); // imprime valor da temperatura
        ir_send_coolix(temp_codes[current_temp_index], nBitsCoolix, NREPEAT);
    } else {
        uart_write("Temperatura já está no máximo (30C)\r\n");
    }
}

void decrease_temperature() {
    if (current_temp_index > TEMP_MIN_INDEX) {
        current_temp_index--;
        uart_write("Diminuindo temperatura para ");
        uart_write_int_ln(temp_values[current_temp_index]); // imprime valor da temperatura
        ir_send_coolix(temp_codes[current_temp_index], nBitsCoolix, NREPEAT);
    } else {
        uart_write("Temperatura já está no mínimo (18C)\r\n");
    }
}


// compara e dispara IR
void process_command(const char *cmd) {
    for (uint8_t i = 0; commands[i] != NULL; i++) {
        if (strcmp(cmd, commands[i]) == 0) {
            send_ir_command(i);
            return;
        }
    }
    // comando não reconhecido
    uart_write("Comando invalido\r\n");
}

// stub do envio IR
void send_ir_command(uint8_t cmd_id) {
    switch (cmd_id) {
        case 0:  // "onac"
            uart_write("Enviando comando de ligar ac 23C\r\n");
            ir_send_coolix(LIGARAC23_COOLIX, nBitsCoolix, NREPEAT);
            break;
        case 1:  // "offac"
            uart_write("Enviando comando de desligar o ac\r\n");
            ir_send_coolix(DESLIGARAC_COOLIX, nBitsCoolix, NREPEAT);
            break;
        case 2: // "temp18"
            uart_write("Trocando temperatura para 18C\r\n");
            ir_send_coolix(TEMPERATURA18_COOLIX, nBitsCoolix, NREPEAT);
            current_temp_index = 0;
            break;
        case 3: // "temp19"
            uart_write("Trocando temperatura para 19C\r\n");
            ir_send_coolix(TEMPERATURA19_COOLIX, nBitsCoolix, NREPEAT);
            current_temp_index = 1;
            break;
        case 4: // "temp20"
            uart_write("Trocando temperatura para 20C\r\n");
            ir_send_coolix(TEMPERATURA20_COOLIX, nBitsCoolix, NREPEAT);
            current_temp_index = 2;
            break;
        case 5: // "temp21"
            uart_write("Trocando temperatura para 21C\r\n");
            ir_send_coolix(TEMPERATURA21_COOLIX, nBitsCoolix, NREPEAT);
            current_temp_index = 3;
            break;
        case 6: // "temp22"
            uart_write("Trocando temperatura para 22C\r\n");
            ir_send_coolix(TEMPERATURA22_COOLIX, nBitsCoolix, NREPEAT);
            current_temp_index = 4;
            break;
        case 7: // "temp23"
            uart_write("Trocando temperatura para 23C\r\n");
            ir_send_coolix(TEMPERATURA23_COOLIX, nBitsCoolix, NREPEAT);
            current_temp_index = 5;
            break;
        case 8: // "temp24"
            uart_write("Trocando temperatura para 24C\r\n");
            ir_send_coolix(TEMPERATURA24_COOLIX, nBitsCoolix, NREPEAT);
            current_temp_index = 6;
            break;
        case 9: // "temp25"
            uart_write("Trocando temperatura para 25C\r\n");
            ir_send_coolix(TEMPERATURA25_COOLIX, nBitsCoolix, NREPEAT);
            current_temp_index = 7;
            break;
        case 10: // "temp26"
            uart_write("Trocando temperatura para 26C\r\n");
            ir_send_coolix(TEMPERATURA26_COOLIX, nBitsCoolix, NREPEAT);
            current_temp_index = 8;
            break;
        case 11: // "temp27"
            uart_write("Trocando temperatura para 27C\r\n");
            ir_send_coolix(TEMPERATURA27_COOLIX, nBitsCoolix, NREPEAT);
            current_temp_index = 9;
            break;
        case 12: // "temp28"
            uart_write("Trocando temperatura para 28C\r\n");
            ir_send_coolix(TEMPERATURA28_COOLIX, nBitsCoolix, NREPEAT);
            current_temp_index = 10;
            break;
        case 13: // "temp29"
            uart_write("Trocando temperatura para 29C\r\n");
            ir_send_coolix(TEMPERATURA29_COOLIX, nBitsCoolix, NREPEAT);
            current_temp_index = 11;
            break;
        case 14: // "temp30"
            uart_write("Trocando temperatura para 30C\r\n");
            ir_send_coolix(TEMPERATURA30_COOLIX, nBitsCoolix, NREPEAT);
            current_temp_index = 12;
            break;
        case 15: // "ven"
            uart_write("Ativando modo ventilador\r\n");
            ir_send_coolix(MUDARDIRECAO_COOLIX, nBitsCoolix, NREPEAT);
            break;
        case 16: // "it++"
            increase_temperature();
            break;
        case 17: // "it--"
            decrease_temperature();
            break;
        default:
            uart_write("Comando inválido\r\n");
            break;
    }
}



