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

#define MAX_NO_OF_HANDLES 8

typedef struct {
    EventHandler *eventHandler;
    PollEvent poll;
    uint16_t timeOut;
    bool isUsed;
} HandleRegistration;

void regist_event(EventHandler* eventHandler);
void unregist_event(EventHandler* eventHandler);
void reload_event(EventHandler* eventHandler);

#endif
