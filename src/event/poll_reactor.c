#include <event/poll_reactor.h>
#include <event/event.h>
#include <event/handle.h>

static HandlerRegistration registerHandlers[MAX_NO_OF_HANDLER];

bool add_to_registry(EventHandler* eventHandler);
bool remove_from_registry(EventHandler* eventHandler);

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
            freeEntry->fd.fd = handle.fd;
            freeEntry->fd.timeOut = handle.timerPreset;
            
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

void timer_tick()
{
    
}
