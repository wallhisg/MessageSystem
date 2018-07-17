#ifndef POLL_REACTOR_H
#define POLL_REACTOR_H

#include <system/debug.h>
#include <event/error.h>
#include <event/event.h>
#include <event/event_handler.h>
//#include <event/pool_event.h>

#define MAX_NO_OF_HANDLER 32

// Define pool event
typedef struct {
    EventFd fd;
    uint16_t timeOut;
} PoolEvents;

typedef struct {
    bool isUsed;
    EventHandler* eventHandler;
    PoolEvents fd;
} HandlerRegistration;

void timer_tick();


#endif  //  POLL_REACTOR_H
