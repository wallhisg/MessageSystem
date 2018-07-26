#include "TEST_HANDLE.h"


#ifndef LOOP
#define LOOP    10
#endif

// Test handle with persistent are TRIBOOL_FALSE, TRIBOOL_TRUE
void TEST_HANDLE_EVENT()
{
    Handle handle = {0};
    handle.eds = event_description(ET_SEND, PT_TX_UART, ET_READ, PT_GPIO);
    handle.ad.address = 0x55;
    handle.ad.value = 0xAA;
    handle.persistent = TRIBOOL_TRUE;
    handle.timerPreset = 0;

    printf("BEFORE\r\n");
    printf("handle.eds.event.fields.et: %d\r\n", handle.eds.event.fields.et);
    printf("handle.eds.event.fields.pt: %d\r\n", handle.eds.event.fields.pt);

    printf("handle.eds.revent.fields.et: %d\r\n", handle.eds.revent.fields.et);
    printf("handle.eds.revent.fields.pt: %d\r\n", handle.eds.revent.fields.pt);

    printf("handle.buff.address: %d\r\n", handle.ad.address);
    printf("handle.buff.value: %d\r\n", handle.ad.value);

    create_event(handle);
    timer_tick();
    handle_events();
    timer_tick();
    handle_events();

    Event *event0 = get_system_event(0);

    printf("MAIN\r\n");
    printf("handle address %p\r\n", &event0->handle);
    printf("handle.eds.event.value: %d\r\n", event0->handle.eds.event.value);
    printf("handle.timerPreset: %d\r\n", event0->handle.timerPreset);
}

// Test handle with persistent are TRIBOOL_INDETERMINATE
void TEST_HANDLE_EVENT_WITH_PERSISTENT()
{
    Handle handle = {0};
    handle.eds = event_description(ET_WRITE, PT_GPIO, ET_WRITE, PT_GPIO);
    handle.ad.address = 0x55;
    handle.ad.value = 0xAA;
    handle.persistent = TRIBOOL_INDETERMINATE;
    handle.timerPreset = 0;

    printf("BEFORE\r\n");
    printf("handle.eds.event.fields.et: %d\r\n", handle.eds.event.fields.et);
    printf("handle.eds.event.fields.pt: %d\r\n", handle.eds.event.fields.pt);

    printf("handle.eds.revent.fields.et: %d\r\n", handle.eds.revent.fields.et);
    printf("handle.eds.revent.fields.pt: %d\r\n", handle.eds.revent.fields.pt);

    printf("handle.buff.address: %d\r\n", handle.ad.address);
    printf("handle.buff.value: %d\r\n", handle.ad.value);

    create_event(handle);

    int i =0;
    for(i = 0; i < LOOP; ++i)
    {
        timer_tick();
        handle_events();
    }

    Event *event0 = get_system_event(0);

    printf("MAIN\r\n");
    printf("handle address %p\r\n", &event0->handle);
    printf("handle.eds.event.value: %d\r\n", event0->handle.eds.event.value);
    printf("handle.timerPreset: %d\r\n", event0->handle.timerPreset);
}
