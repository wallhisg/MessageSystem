#include <event/event.h>



void event_init()
{
    
}

Handle get_handle(void *instance)
{
    const EventPtr event_ = instance;

    return event_->handle;
}
