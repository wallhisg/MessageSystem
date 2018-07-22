#include <stdio.h>
#include <system/system.h>
#include <event/handle.h>
#include <event/event.h>
#include <event/event_loop.h>
#include <event/reactor.h>

int main()
{
    printf("----- TEST_HANDLE_EVENT -----\r\n");
    system_init();
    
    Handle handle = {0};
    handle.eds = event_description(ET_SEND, PT_UART, ET_READ, PT_GPIO);
    handle.buff.address = 0x55;
    handle.buff.value = 0xAA;
    handle.timerPreset = 0;

    printf("BEFORE\r\n");
    printf("handle.eds.event.fields.et: %d\r\n", handle.eds.event.fields.et);
    printf("handle.eds.event.fields.pt: %d\r\n", handle.eds.event.fields.pt);

    printf("handle.eds.revent.fields.et: %d\r\n", handle.eds.revent.fields.et);
    printf("handle.eds.revent.fields.pt: %d\r\n", handle.eds.revent.fields.pt);

    printf("handle.buff.address: %d\r\n", handle.buff.address);
    printf("handle.buff.value: %d\r\n", handle.buff.value);

    create_event(handle);
    timer_tick();
    handle_events();
//    timer_tick();
//    handle_events();
//    timer_tick();
//    handle_events();

    Event *event0 = get_system_event(0);
    
    printf("MAIN\r\n");
    printf("handle address %p\r\n", &event0->handle);
    printf("handle.eds.event.value: %d\r\n", event0->handle.eds.event.value);
    printf("handle.timerPreset: %d\r\n", event0->handle.timerPreset);
    return 0; 
}

