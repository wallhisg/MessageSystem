#include <event/reactor.h>
#include <event/event.h>
#include <event/handle.h>
#include <event/reactor_event_loop.h>

static HandlerRegistration registerHandlers[MAX_NO_OF_HANDLER];

bool add_to_registry(EventHandler* eventHandler);
bool remove_from_registry(EventHandler* eventHandler);
int build_event_pool(PoolEvents *poolEvents);
void dispatch_signalled_events(PoolEvents *fds, const int noOfMessages);

void regist_event(EventHandler* eventHandler)
{
    if(eventHandler != NULL)
    {
        if(!add_to_registry(eventHandler))
        {
            error("No more registrations possible");
        }
    }
}

void unregist_event(EventHandler* eventHandler)
{
    if(eventHandler != NULL)
    {
        if(!remove_from_registry(eventHandler))
        {
            error("Event handler not registered");
        }
    }
}

void handle_events(void)
{
    PoolEvents poolEvents[MAX_NO_OF_HANDLER] = {0};

    const int noOfHandles = build_event_pool(poolEvents);
    printf("noOfHandles %d\r\n", noOfHandles);
    int i = 0;
    for(i = 0; i < noOfHandles; ++i)
    {
        printf("poolEvents[%d].timeOut %d\r\n", i, poolEvents[i].timeOut);
    }
 
    
    if(noOfHandles > 0)
    {
        dispatch_signalled_events(poolEvents, noOfHandles);
    }


}

bool add_to_registry(EventHandler* eventHandler)
{
    bool isRegistered = false;
    
    int i = 0;
    for(i = 0; (i < MAX_NO_OF_HANDLER) && (isRegistered == false); ++i)
    {
        if(registerHandlers[i].isUsed == false)
        {
            Handle handle = get_handle(eventHandler->instance);
            
            HandlerRegistration* freeEntry = &registerHandlers[i];
            freeEntry->eventHandler= eventHandler;
            freeEntry->poolEvent.fd = handle.fd;
            freeEntry->poolEvent.timeOut = handle.timerPreset;
            
            freeEntry->isUsed = isRegistered = true;
            debug("Reactor: Added eventHandler with ID = %d\n", handle.fd.id);
        }
    }
    
    return isRegistered;
}

bool remove_from_registry(EventHandler* eventHandler)
{
    bool nodeRemoved = false;

    int i = 0;
    for(i = 0; (i < MAX_NO_OF_HANDLER) && (nodeRemoved == false); ++i)
    {
        if((registerHandlers[i].isUsed) && (registerHandlers[i].eventHandler == eventHandler))
        {
            registerHandlers[i].isUsed = false;
            nodeRemoved = 1;
            
            Handle handle = get_handle(eventHandler->instance);
            debug("Reactor: Removed eventHandler with type %d\n", handle.fd.id);
        }
    }
    
    return nodeRemoved;

}

int build_event_pool(PoolEvents *poolEvents)
{
    int noOfCopiedHandles = 0;

    int i = 0;
    for(i = 0; i < MAX_NO_OF_HANDLER; ++i)
    {
        if((registerHandlers[i].isUsed) && (registerHandlers[i].poolEvent.poll == POLLVAL))
        {
            poolEvents[noOfCopiedHandles] = registerHandlers[i].poolEvent;
            ++noOfCopiedHandles;
        }
    }

    return noOfCopiedHandles;
}

EventHandler *find_eventHandler(EventFd fd)
{
    EventHandler *matchingHandler = NULL;

    int i = 0;
    for(i = 0; (i < MAX_NO_OF_HANDLER) && matchingHandler == NULL; ++i)
    {
        if((registerHandlers[i].poolEvent.fd.id == fd.id) && (registerHandlers[i].poolEvent.poll == POLLVAL))
        {
            matchingHandler = registerHandlers[i].eventHandler;
        }
    }

    return matchingHandler;
}

void dispatch_signalled_events(PoolEvents *fds, const int noOfMessages)
{
    int i = 0;
    for(i = 0; i < noOfMessages; ++i)
    {
        EventHandler *signalledHandler = find_eventHandler(fds[i].fd);

        if(signalledHandler != NULL)
        {
            debug_message("dispatch_signalled_events");
            signalledHandler->handleEvent(signalledHandler->instance);
        }
        else
        {
            debug_message("signalledHandler is NULL");
        }

    }
}

void timer_tick()
{
    int noOfCopiedHandles = 0;

    int i = 0;
    for(i = 0; i < MAX_NO_OF_HANDLER; ++i)
    {
        if(registerHandlers[i].isUsed)
        {
            if(registerHandlers[i].poolEvent.timeOut > 0)
            {
                registerHandlers[i].poolEvent.timeOut--;
                registerHandlers[i].poolEvent.poll = POLLHUP;
            }
            else
                registerHandlers[i].poolEvent.poll = POLLVAL;

            ++noOfCopiedHandles;
        }
    }
    for(i = 0; i < noOfCopiedHandles; ++i)
    {
        printf("registerHandlers[%d].fd.timeOut: %d\r\n", i,registerHandlers[i].poolEvent.timeOut);
    }
}
