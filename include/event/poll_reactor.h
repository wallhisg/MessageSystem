#ifndef POLL_REACTOR_H
#define POLL_REACTOR_H

#include <system/debug.h>
#include <event/error.h>
#include <event/event_handler.h>


#define MAX_NO_OF_HANDLER 32

typedef struct {
    bool isUsed;
    EventHandler eventHandler;
} HandlerRegistration;




#endif  //  POLL_REACTOR_H
