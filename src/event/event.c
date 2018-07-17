#include <event/event.h>
#include <event/reactor.h>


static Event SYSTEM_EVENT[MAX_NO_OF_EVENTS];



int find_free_event_slot();
int find_matching_eventHandler_slot(const EventHandler *eventHandler);
void on_closed_event(void *closedEvent);
void *event_demultiplexer(void *instance);

void event_init()
{
    int i = 0;

    for(i = 0; i < MAX_NO_OF_EVENTS; ++i)
    {
        SYSTEM_EVENT[i].handle.fd.id = 0;
    }
}

void create_event(Handle handle)
{
    int eventSlot = find_free_event_slot();
    printf("eventSlot %d\r\n", eventSlot);

    if(eventSlot >= 0)
    {
        EventPtr event = &SYSTEM_EVENT[eventSlot];
        event->handle = handle;

        EventHandlerPtr eventHandler = &event->eventHandler;
        eventHandler->instance = event;
        eventHandler->getHandle = get_handle;
        eventHandler->handleEvent = (void*)event_demultiplexer;
        event->notifier.events = &SYSTEM_EVENT;
        event->notifier.onEventClosed = on_closed_event;

        regist_event(&event->eventHandler);
    }
    else
        debug_message("create_event: FALSE");
}


void destroy_event(Event *event)
{
    Handle handle = event->handle;
//    debug("handle - timerPreset: %d\r\n", handle.timerPreset);
    if(handle.persistent == false)
    {
        unregist_event(&event->eventHandler);
        event->handle.fd.id = 0;
    }
}

void on_closed_event(void *closedEvent)
{
    EventHandler *eventHandler = closedEvent;
    int eventHandlerSlot = find_matching_eventHandler_slot(eventHandler);

    if(eventHandlerSlot < 0)
    {
        error("Phantom eventHandler detected");
    }
    else {
        destroy_event(eventHandler->instance);
    }
}

Handle get_handle(void *instance)
{
    const EventPtr event_ = instance;

    return event_->handle;
}


int find_free_event_slot()
{
    int eventSlot = -1;
    int slotFound = 0;

    int i = 0;
    for(i = 0; (i < MAX_NO_OF_EVENTS) && (slotFound == 0); ++i)
    {
        if(SYSTEM_EVENT[i].handle.fd.id == 0)
        {
            eventSlot = i;
            slotFound = 1;
        }
    }

    return eventSlot;
}

int find_matching_eventHandler_slot(const EventHandler *eventHandler)
{
    int eventHandlerSlot = -1;
    int slotFound = 0;

    int i = 0;
    for(i = 0; (i < MAX_NO_OF_EVENTS) && slotFound == 0; ++i)
    {
        if(&SYSTEM_EVENT[i].eventHandler == eventHandler)
        {
            eventHandlerSlot = i;
            slotFound = 1;
        }
    }

    return eventHandlerSlot;
}


Event *get_system_event(const int i)
{
    return &SYSTEM_EVENT[i];
}

void *event_demultiplexer(void *instance)
{
    printf("event_demultiplexer\r\n");
}
