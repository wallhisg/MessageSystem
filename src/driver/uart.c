#include <driver/uart.h>
#include <event/handle.h>
#include <event/event.h>

#define UART_RX_BUFFER_LENGTH   64
#define UART_TX_BUFFER_LENGTH   64

static char UART_RX_BUFFER[UART_RX_BUFFER_LENGTH];
static char UART_TX_BUFFER[UART_TX_BUFFER_LENGTH];
static Buffer rxBuf;
static Buffer txBuf;

void uart_init()
{
    // init rxBuffer
    rxBuf.buffer = UART_RX_BUFFER;
    rxBuf.size = UART_RX_BUFFER_LENGTH;
    rxBuf.head = rxBuf.tail = rxBuf.buffer;
    buffer_reset(&rxBuf);

    // init txBuffer
    txBuf.buffer = UART_TX_BUFFER;
    txBuf.size = UART_TX_BUFFER_LENGTH;
    txBuf.head = txBuf.tail = txBuf.buffer;
    buffer_reset(&txBuf);
}

void uart_rx_isr(uint8_t byte)
{
    char data;
    data = (char)(byte);

    if((data != CR) && (data != '\0'))
    {
        buffer_write_one_byte(&rxBuf, data);
    }

    if(data == LF)
    {
        Handle handle = {0};
        handle.eds = event_description(ET_NONE, PT_NONE, ET_PARSER, PT_RX_UART);
        handle.persistent = TRIBOOL_FALSE;
        handle.timerPreset = 0;
        create_event(handle);
    }

}

void uart_tx_isr(char data)
{
    debug_message("uart_tx_isr");
    uint8_t byte = (uint8_t)(data);

    printf("uart send byte: %d\r\n", byte);

}

Buffer *get_uart_rx_buffer()
{
    return &rxBuf;
}

Buffer *get_uart_tx_buffer()
{
    return &txBuf;
}

void uart_rx_parser()
{
    debug_message("uart_rx_parser");
}

void write_one_byte_to_uart_rx_buffer(char byte)
{
    buffer_write_one_byte(&rxBuf, byte);
}

char read_one_byte_from_uart_rx_buffer()
{
    return buffer_read_one_byte(&rxBuf);
}
