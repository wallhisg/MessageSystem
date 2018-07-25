#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>
#include <string.h>
#include <system/system.h>

#define LF      0x0A    //  '\n' - New Line
#define CR      0x0D    //  '\r' - Enter

typedef enum {
    RING_STATUS_EMPTY = 0,
    RING_STATUS_DATA_PRESENT = 1,
    RING_STATUS_FULL = 2
} BufferStatus;

typedef struct {
    char *head;
    char *tail;
    char *buffer;
    uint8_t  size;
    BufferStatus status;
} Buffer, *BufferPtr;

void buffer_reset(BufferPtr buff);

void buffer_write_one_byte(Buffer *buff, const uint8_t byte);
uint16_t buffer_write_bytes(BufferPtr buff, uint8_t* bytes);

const char buffer_read_one_byte(BufferPtr buff);
uint16_t buffer_read_bytes(char *result,  BufferPtr buff);

const uint16_t buffer_bytes_used(const BufferPtr buff);
const BufferStatus get_buffer_status(BufferPtr buff);

#endif // RING_BUFFER_H
