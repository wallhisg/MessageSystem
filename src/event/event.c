#include <event/event.h>

HandleEvent get_event_handle(void *event)
{
    const EventPtr event_ = event;

    return event_->eventHandle;
}
