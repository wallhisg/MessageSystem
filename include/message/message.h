#ifndef MESSAGE_H
#define MESSAGE_H

#include <system/system.h>

typedef enum {
    ENDPOINT_UNDEFINE,
    ENDPOINT_GPIO,
    ENDPOINT_UART,
    ENDPOINT_ADC
} EndpointType;

typedef enum {
    NONE, ON, OFF,
    START, STOP,
    READ, WRITE,
    SET, GET, CLEAR, TOGGLE,
    ENABLE, DISABLE
} EventType;

typedef enum {
    COMMAND,        //  LOCAL: Address - Value Pair
    DOCUMENT,       //  REMOTE: JSON
    EVENT,          //  JSON
    REQUEST_REPLY   //  LOCAL & REMOTE: Json; Address - Value Pair
} MessageType;

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

typedef MessageHandle (*get_handle_func)(void * instance);

typedef void* (*handle_event_func)(void *);
typedef void (*on_event_closed_func)(void* closedEvent);

typedef struct {
    EventType event;
    handle_event_func handleEvent;
    on_event_closed_func onEventClose;
} Event, *EventPtr;

typedef struct {
    MessageHandle handle;
    void *instance;
    bool isUsed;
} Message, *MessagePtr;

MessageHandle get_handle(void *message);
void handle_message();
void create_message(MessageHandle handle, handle_event_func handleEvent);
void destroy_message();

#endif  //  MESSAGE_H
