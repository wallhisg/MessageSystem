#ifndef CHANNEL_H
#define CHANNEL_H

#include <system/system.h>
#include <message/message.h>
#include <message/endpoint/endpoint.h>

#define MAX_NO_OF_UART_MESSAGE  4
#define MAX_NO_OF_SPI_MESSAGE   4
#define MAX_NO_OF_I2C_MESSAGE   4



typedef struct {
    MessagePtr messages;
    size_t size;
} Channel, *ChannelPtr;

void channel_init();
ChannelPtr get_channel(EndpointType epType);

int find_free_message_slot(Message message[], size_t size);

#endif  //  CHANNEL_H

