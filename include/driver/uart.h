#ifndef UART_H
#define UART_H

#include <system/system.h>
#include "ring_buffer.h"

void uart_init();

void uart_rx_isr(uint8_t byte);
void uart_rx_parser();

void write_one_byte_to_uart_rx_buffer(char byte);
char read_one_byte_from_uart__rx_buffer();

void uart_tx_isr(char data);

Buffer *get_uart_rx_buffer();
Buffer *get_uart_tx_buffer();



#endif // UART_H
