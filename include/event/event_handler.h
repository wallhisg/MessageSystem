#ifndef _EVENT_HANDLER_H_
#define _EVENT_HANDLER_H_

#include <event/handle.h>

typedef Handle (*get_handle_func)(void * instance);
typedef void (*handle_event_func)(void *instance);

typedef struct {
    void* instance;
    get_handle_func getHandle;
    handle_event_func handleEvent;
} EventHandler, *EventHandlerPtr;

#endif  //  _EVENT_HANDLER_H_
