#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <system/system.h>
#include <event/handle.h>
#include <event/event.h>
#include <driver/ring_buffer_manager.h>

#define MAX_NO_OF_BUFFER    64
static char buffer[MAX_NO_OF_BUFFER];
volatile uint16_t bytesWritten = 0;

void TEST_WRITE_ONE_BYTE_TO_BUFFER()
{
    debug("TEST_WRITE_ONE_BYTE_TO_BUFFER\r\n");

    // init value to write
    char *bytesWrite = "abcdef\n";
    int bytesWritten = strlen(bytesWrite);

    memset(buffer, 0, MAX_NO_OF_BUFFER);
    memcpy(buffer, bytesWrite, bytesWritten);
    printf("*** bytesWrite length %d\r\n", bytesWritten);
    printf("*** string input: %s\r\n", buffer);

    Buffer *rxBuff = get_uart_rx_buffer();

    uint8_t byte;
    int i = 0;
    for(i = 0; i < bytesWritten; i++)
    {
        byte = buffer[i];
        buffer_write_one_byte(rxBuff, byte);
    }
    printf("ByteWritten: %d\r\n", bytesWritten);
    printf("Bytes used: %d\r\n", buffer_bytes_used(rxBuff));
}

void TEST_WRITE_BYTES_TO_BUFFER()
{
    debug("TEST_WRITE_BYTES_TO_BUFFER\r\n");

    // init value to write
    char *bytesWrite = "123456\n";
    int bytesWritten = strlen(bytesWrite);

    memset(buffer, 0, MAX_NO_OF_BUFFER);
    memcpy(buffer, bytesWrite, bytesWritten);
    printf("*** bytesWrite length %d\r\n", bytesWritten);
    printf("*** string input: %s\r\n", buffer);

    Buffer *rxBuff = get_uart_rx_buffer();

    bytesWritten = buffer_write_bytes(rxBuff, buffer);
    printf("ByteWritten: %d\r\n", bytesWritten);
    printf("Bytes used: %d\r\n", buffer_bytes_used(rxBuff));
}

void TEST_READ_FROM_BUFFER_ONE_BYTE()
{
    debug("TEST_READ_FROM_BUFFER_ONE_BYTE\r\n");
    memset(buffer, 0, MAX_NO_OF_BUFFER);

    Buffer *rxBuff = get_uart_rx_buffer();
    char byte;
    int i = 0;
    for(i = 0; i < rxBuff->size; i++)
    {
        byte = buffer_read_one_byte(rxBuff);
        if(rxBuff->status != RING_STATUS_EMPTY)
        {
            buffer[i] = byte;
        }
    }
    printf("%s\r\n", buffer);
}

void TEST_READ_FROM_BUFFER_BYTES()
{
    printf("\r\n");
    debug("TEST_READ_FROM_BUFFER_BYTES\r\n");

    Buffer *rxBuff = get_uart_rx_buffer();
    uint16_t bytesWritten = buffer_read_bytes(buffer, rxBuff);

    printf("*** bytesRead length: %d\r\n", bytesWritten);
    printf("*** bytesRead value: %s\r\n", buffer);
    printf("\r\n");
}

int main()
{
    printf("----- TEST_RING_BUFFER -----\r\n");
    system_init();

    Buffer *rxBuff = get_uart_rx_buffer();
    buffer_reset(rxBuff);

    TEST_WRITE_ONE_BYTE_TO_BUFFER();
    TEST_WRITE_BYTES_TO_BUFFER();

    memset(buffer,0, MAX_NO_OF_BUFFER);
    TEST_READ_FROM_BUFFER_ONE_BYTE();
    memset(buffer,0, MAX_NO_OF_BUFFER);
    TEST_READ_FROM_BUFFER_BYTES();

    return 0; 
}

