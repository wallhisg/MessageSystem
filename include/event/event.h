#ifndef EVENT_H
#define EVENT_H

#include <stdint.h>
#include <stdbool.h>
#include <system/system.h>
#include <event/handle.h>
#include <event/event_handler.h>
#include <event/event_notifier.h>

#define MAX_NO_OF_EVENTS    16

typedef struct {
    Handle handle;
    EventHandler eventHandler;
    EventNotifier notifier;
} Event, *EventPtr;

EventDescription event_description(uint8_t REVENT_ET, uint8_t REVENT_PT,
                           uint8_t EVENT_ET, uint8_t EVENT_PT);

void event_init();

Handle get_handle(void *instance);
Handle *get_handle_by_pointer(void *instance);
void create_event(Handle handle);
void destroy_event(Event *event);

Event *get_system_event(const int i);

#endif // EVENT_H
