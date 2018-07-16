#ifndef EVENT_NOTIFIER_H
#define EVENT_NOTIFIER_H

typedef void (*on_event_closed_func)(void* events, void* closedEvent);

typedef struct
{
   void* events;
   on_event_closed_func onEventClosed;
} EventNotifier, *EventNotifierPtr;

#endif // EVENT_NOTIFIER_H
