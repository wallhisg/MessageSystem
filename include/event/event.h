#ifndef EVENT_H
#define EVENT_H

#include <stdbool.h>
#include <system/system.h>
#include <event/handle.h>
#include <event/event_handler.h>
#include <event/event_notifier.h>


typedef struct {
    Handle handle;
    EventHandler eventHandler;
    EventNotifier notifier;
} Event, *EventPtr;

// Define poll event file description
typedef struct {
    uint16_t fd;             /* file descriptor */
    uint8_t events;       /* requested events */
    uint8_t revents;     /* returned events */
} PollEventFd; 

Handle get_handle(void *instance);

void event_init();


#endif // EVENT_H
