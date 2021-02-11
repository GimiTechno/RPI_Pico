#ifndef __UART_H__
#define __UART_H__

#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

#define ISR
#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1

void UART_Init(void);

#endif /* __UART_H__ */