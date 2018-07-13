#ifndef EVENT_H
#define EVENT_H

#include <system/system.h>

typedef enum {
    EVENT_READ, EVENT_WRITE,
    EVENT_SET, EVENT_GET, EVENT_CLEAR, EVENT_TOGGLE,
    EVENT_ENABLE, EVENT_DISABLE
} HandleEvent;

typedef struct {
    uint16_t preset;
    uint16_t counter;
} Timer;

typedef HandleEvent (*get_handle_func)(void * instance);
typedef void* (*handle_event_func)(void *instance);

typedef struct {
    void* instance;
    get_handle_func getHandle;
    handle_event_func handleEvent;
} EventHandler, *EventHandlerPtr;

//typedef struct {
//    HandleEvent handle;
//    handle_event_func handleEvent;
//    on_event_closed_func onEventClose;
//    void *instance;
//} Event, *EventPtr;

HandleEvent get_event_handle(void *event);


#endif // EVENT_H
