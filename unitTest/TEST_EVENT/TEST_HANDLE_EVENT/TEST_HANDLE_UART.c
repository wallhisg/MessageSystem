#include "TEST_HANDLE_UART.h"

#ifndef LOOP
#define LOOP    10
#endif

void TEST_UART_RX()
{
    debug_message("TEST_UART_RX");

    // init data and variable
    int i =0;
    uint16_t len;

    char *data = "Hello World\r\n";
    len = strlen(data);
    printf("data length %d\r\n", len);

    uint8_t byteWrite[len];

    // convert char to uint8_t and copy to uint8_t array
    for(i = 0; i < len; ++i)
    {
        byteWrite[i] = (uint8_t)data[i];
    }

    // write data to uart rx buffer
    len = sizeof(byteWrite);
    printf("byteWrite length %d\r\n", len);
    for(i = 0; i < len; ++i)
    {
        uart_rx_isr(byteWrite[i]);
    }

    // do event loops
    for(i = 0; i < LOOP; ++i)
    {
        timer_tick();
        handle_events();
    }

    Buffer *rxBuff = get_uart_rx_buffer();
    printf("rxBuff: %s\r\n", rxBuff->buffer);
    printf("rxBuff byte used %d\r\n", buffer_bytes_used(rxBuff));
}

void TEST_UART_TX()
{

}
