/********************************************************************
* (C) Adam Petersen 2005
*
* This code accompanies the article "Patterns in C, part 5: REACTOR".
* The article is available as PDF from www.adampetersen.se
*
* The code is intended as a illustration of the Reactor at work and 
* is not suitable for use in production code (in order to keep this 
* example as short as possible, the error handling has been strongly 
* simplified).
*
********************************************************************/

#ifndef REACTOR_H
#define REACTOR_H

#include <event/event_handler.h>

#define MAX_NO_OF_HANDLER 8


// Define pool event
typedef struct {
    EventFd fd;
    PollEvent poll;
    uint16_t timeOut;
} PoolEvents;

typedef struct {
    bool isUsed;
    EventHandler* eventHandler;
    PoolEvents poolEvent;
} HandlerRegistration;

void regist_event(EventHandler* eventHandler);
void unregist_event(EventHandler* eventHandler);

#endif
