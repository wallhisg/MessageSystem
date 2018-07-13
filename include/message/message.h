#ifndef MESSAGE_H
#define MESSAGE_H

#include <system/system.h>
#include <event/event.h>

typedef enum {
    COMMAND,        //  LOCAL: Address - Value Pair
    DOCUMENT,       //  REMOTE: JSON
    EVENT,          //  JSON
    REQUEST_REPLY   //  LOCAL & REMOTE: Json; Address - Value Pair
} MessageType;

typedef enum {
    ENDPOINT_UNDEFINE,
    UART_ENDPOINT,
    SPI_ENDPOINT,
    I2C_ENDPOINT
} EndpointType;

typedef enum {
    POINT_TO_POINT,
    PUBLISH_SUBSCRIBE,
    DATA_TYPE,
    DEAD_LETTER,
    GUARANTEED
} ChannelType;

typedef enum {
    PIPES_AND_FILTER,
    CONTENT_BASED_ROUTER,
    CONTENT_AGGREGATOR
} RoutingType;

typedef struct {
    EndpointType endpoint;
    ChannelType channel;
    MessageType type;
    RoutingType router;
} MessageHandle;

typedef struct {
    MessageHandle handle;
    void *instance;
    bool isUsed;
} Message, *MessagePtr;

MessageHandle get_message_handle(void *message);


void handle_message();
void create_message();
void destroy_message();

#endif  //  MESSAGE_H
