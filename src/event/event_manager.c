#include <event/event_manager.h>

void handle_events_by_description(Handle *handle)
{
    printf("handle_events_by_description\r\n");
    printf("handle->timerPreset: %d\r\n", handle->timerPreset);
    handle->timerPreset = 14;
    handle->eds.event.value = 10;
}
