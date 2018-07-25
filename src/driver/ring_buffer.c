#include <driver/ring_buffer.h>

void buffer_reset(BufferPtr buff)
{
    memset(buff->buffer, 0, buff->size);
    buff->head = buff->tail = buff->buffer;
    buff->status = RING_STATUS_EMPTY;
}

void buffer_write_one_byte(Buffer *buff, const uint8_t byte)
{
    // accept ascii code <= 127
    if(byte <= 127)
    {
        if (buff->status == RING_STATUS_FULL)
        {
            debug("MSG_UART_RING_FULL");
            buffer_reset(buff);
            return;
        }

        *buff->tail = byte;
        buff->tail++;

        if (buff->tail == (buff->buffer + buff->size))
            buff->tail = buff->buffer;

        buff->status = RING_STATUS_DATA_PRESENT;

        if (buff->tail == buff->head)
            buff->status = RING_STATUS_FULL;
    }
}

uint16_t buffer_write_bytes(BufferPtr buff, uint8_t* bytes)
{
    uint16_t numBytesWritten = 0;
    uint8_t byteWrite;
    while (numBytesWritten < buff->size)
    {
        if (buff->status == RING_STATUS_FULL)
            break;

        byteWrite = bytes[numBytesWritten];
        if ((byteWrite != LF) || (byteWrite != CR))
            buffer_write_one_byte(buff, byteWrite);
        else
        {
            buffer_write_one_byte(buff, byteWrite);
            break;
        }
    }

    return numBytesWritten;
}

const char buffer_read_one_byte(BufferPtr buff)
{
    char byteRead = 0;
    byteRead = *buff->head;
    *buff->head = ' ';  // rewrite space
    buff->head++;

    if (buff->head == buff->buffer + buff->size)
        buff->head = buff->buffer;

    if (buff->head == buff->tail)
        buff->status = RING_STATUS_EMPTY;
    else
        buff->status = RING_STATUS_DATA_PRESENT;

    return byteRead;
}

uint16_t buffer_read_bytes(char *result, BufferPtr buff)
{
    uint16_t numBytesRead = 0;

    while (numBytesRead < buff->size)
    {
        if (buff->status == RING_STATUS_EMPTY)
            break;
        else
        {
            result[numBytesRead++] = buffer_read_one_byte(buff);
        }
    }

    return numBytesRead;
}

const uint16_t buffer_bytes_used(const BufferPtr buff)
{
    uint16_t bytesUsed = 0;

    if (buff->status == RING_STATUS_EMPTY)
        bytesUsed = 0;
    else if (buff->tail > buff->head)
        bytesUsed = (buff->tail - buff->head);
    else
        bytesUsed = (buff->size - (buff->head - buff->tail));

    return bytesUsed;
}

const BufferStatus get_buffer_status(BufferPtr buff)
{
    return buff->status;
}
