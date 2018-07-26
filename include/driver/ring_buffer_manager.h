#ifndef RING_BUFFER_MANAGER_H
#define RING_BUFFER_MANAGER_H

#include <system/system.h>
#include <driver/ring_buffer.h>

void ring_buffer_init();

void uart_buffer_init(void);
Buffer *get_uart_rx_buffer();
Buffer *get_uart_tx_buffer();


#endif  //  RING_BUFFER_MANAGER_H
