#include <system/system.h>
#include <event/reactor.h>
#include <event/event.h>
#include <event/handle.h>
#include <event/event_loop.h>

static HandleRegistration registerHandles[MAX_NO_OF_HANDLES];

bool add_to_registry(EventHandler* eventHandler);
bool remove_from_registry(EventHandler* eventHandler);
bool reload_from_registry(EventHandler* eventHandler);

int build_eventHandler_pool(EventHandler *eventHandlerPool[]);
void dispatch_signalled_events(EventHandler *eventHandlerPool[], const int noOfMessages);

void regist_event(EventHandler* eventHandler)
{
     debug_message("regist_event");
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
    debug_message("unregist_event");
    if(eventHandler != NULL)
    {
        if(!remove_from_registry(eventHandler))
        {
            error("Event handler not registered");
        }
    }
}

void reload_event(EventHandler* eventHandler)
{
    debug_message("reload_event");
    if(eventHandler != NULL)
    {
        if(!reload_from_registry(eventHandler))
        {
            error("Event handler not reloaded");
        }
    }
}

void handle_events(void)
{
    EventHandler *eventHandlerPool[MAX_NO_OF_HANDLES];

    const int noOfHandles = build_eventHandler_pool(eventHandlerPool);
    
    if(noOfHandles > 0)
    {
        dispatch_signalled_events(eventHandlerPool, noOfHandles);
    }
}

bool add_to_registry(EventHandler* eventHandler)
{
    bool isRegistered = false;
    
    int i = 0;
    for(i = 0; (i < MAX_NO_OF_HANDLES) && (isRegistered == false); ++i)
    {
        if(registerHandles[i].isUsed == false)
        {
            Handle handle = get_handle(eventHandler->instance);
            
            HandleRegistration* freeEntry = &registerHandles[i];
            freeEntry->eventHandler= eventHandler;
            freeEntry->timeOut = handle.timerPreset;
            freeEntry->poll = POLLHUP;
            freeEntry->isUsed = isRegistered = true;
            debug("Reactor: Added eventHandler with ID = %d\n", handle.eds.event.value);
        }
    }
    
    return isRegistered;
}

bool remove_from_registry(EventHandler* eventHandler)
{
    bool nodeRemoved = false;

    int i = 0;
    for(i = 0; (i < MAX_NO_OF_HANDLES) && (nodeRemoved == false); ++i)
    {
        if((registerHandles[i].isUsed) && (registerHandles[i].eventHandler == eventHandler))
        {
            registerHandles[i].isUsed = false;
            nodeRemoved = true;
            
            Handle handle = get_handle(eventHandler->instance);
            debug("Reactor: Removed eventHandler with type %d\n", handle.eds.event.value);
        }
    }
    
    return nodeRemoved;
}

bool reload_from_registry(EventHandler* eventHandler)
{
    bool isReloaded = false;
    
    int i = 0;
    for(i = 0; (i < MAX_NO_OF_HANDLES) && (isReloaded == false); ++i)
    {
        if(registerHandles[i].eventHandler == eventHandler)
        {
            Handle handle = get_handle(eventHandler->instance);
            
            HandleRegistration* freeEntry = &registerHandles[i];
            freeEntry->timeOut = handle.timerPreset;
            freeEntry->poll = POLLHUP;
            freeEntry->isUsed = isReloaded = true;
            debug("Reactor: Reloaded eventHandler with ID = %d\n", handle.eds.event.value);
        }
    }
    
    return isReloaded;
}
int build_eventHandler_pool(EventHandler *eventHandlerPool[])
{
    int noOfCopiedHandles = 0;

    int i = 0;
    for(i = 0; i < MAX_NO_OF_HANDLES; ++i)
    {
        if((registerHandles[i].isUsed) && (registerHandles[i].poll == POLLVAL))
        {
            eventHandlerPool[noOfCopiedHandles] = registerHandles[i].eventHandler;
            ++noOfCopiedHandles;
        }
    }

    return noOfCopiedHandles;
}

void dispatch_signalled_events(EventHandler *eventHandlerPool[], const int noOfMessages)
{
    int i = 0;
    for(i = 0; i < noOfMessages; ++i)
    {
        eventHandlerPool[i]->handleEvent(eventHandlerPool[i]->instance);
    }
}

void timer_tick()
{
    int i = 0;
    for(i = 0; i < MAX_NO_OF_HANDLES; ++i)
    {
        if(registerHandles[i].isUsed)
        {
            if(registerHandles[i].timeOut > 0)
            {
                registerHandles[i].timeOut--;
                registerHandles[i].poll = POLLHUP;
            }
            else
                registerHandles[i].poll = POLLVAL;
        }
    }
}
