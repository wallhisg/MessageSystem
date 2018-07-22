#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <event/handle.h>
#include <driver/gpio.h>

void handle_events_by_description(Handle *handle);
void handle_revent_by_description(Handle *handle);

#endif // EVENT_MANAGER_H
