#include <event/event.h>
#include <event/event_manager.h>
#include <event/reactor.h>


static Event SYSTEM_EVENT[MAX_NO_OF_EVENTS];

int find_free_event_slot();
int find_matching_eventHandler_slot(const EventHandler *eventHandler);
void on_closed_event(void *closedEvent);
void event_demultiplexer(void *instance);

void event_init()
{
    int i = 0;

    for(i = 0; i < MAX_NO_OF_EVENTS; ++i)
    {
        SYSTEM_EVENT[i].handle.eds.event.value = 0;
    }
}

void create_event(Handle handle)
{
    int eventSlot = find_free_event_slot();

    if(eventSlot >= 0)
    {
        EventPtr event = &SYSTEM_EVENT[eventSlot];
        event->handle = handle;

        EventHandlerPtr eventHandler = &event->eventHandler;
        eventHandler->instance = event;
        eventHandler->getHandle = get_handle;
        eventHandler->handleEvent = event_demultiplexer;
        
        event->notifier.events = &SYSTEM_EVENT;
        event->notifier.onEventClosed = on_closed_event;
        regist_event(&event->eventHandler);
    }
    else
        debug_message("create_event: FALSE");
}

void on_closed_event(void *closedEvent)
{
    EventHandler *eventHandler = closedEvent;
    int eventHandlerSlot = find_matching_eventHandler_slot(eventHandler);

    debug("on_closed_event - eventHandlerSlot: %d\r\n", eventHandlerSlot);

    if(eventHandlerSlot < 0)
    {
        error("Phantom eventHandler detected");
    }
    else
    {
        destroy_event(eventHandler->instance);
    }
}

void destroy_event(Event *event)
{
    Handle handle = event->handle;
    if(handle.persistent == TRIBOOL_FALSE)
    {
        unregist_event(&event->eventHandler);
        event->handle.eds.event.value = 0;
    }
    else 
    {
        reload_event(&event->eventHandler);
    }
}

Handle get_handle(void *instance)
{
    const EventPtr event = instance;

    return event->handle;
}

Handle *get_handle_by_pointer(void *instance)
{
    const EventPtr event = instance;
    
    return &event->handle;
}
int find_free_event_slot()
{
    int eventSlot = -1;
    int slotFound = 0;

    int i = 0;
    for(i = 0; (i < MAX_NO_OF_EVENTS) && (slotFound == 0); ++i)
    {
        if(SYSTEM_EVENT[i].handle.eds.event.value == 0)
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

void event_demultiplexer(void *instance)
{
    Handle *handle = get_handle_by_pointer(instance);
    Event *event = instance;
    
    handle_events_by_description(handle);
    handle_revent_by_description(handle);

    event->notifier.onEventClosed(&event->eventHandler);
}

EventDescription event_description(uint8_t REVENT_ET, uint8_t REVENT_PT,
                                   uint8_t EVENT_ET, uint8_t EVENT_PT)
{
    EventDescription eds;
    eds.revent.value = (REVENT_ET << 8 | REVENT_PT);
    eds.event.value = (EVENT_ET << 8 | EVENT_PT);
    return eds;
}








