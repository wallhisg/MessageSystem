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

    handle.eds.event.fields.et = ET_READ;
    handle.eds.event.fields.pt = PT_UART;
    handle.timerPreset = 3;
    handle.persistent = true;
    handle.fileData.address = 0x55;
    handle.fileData.value = 0xAA;

    create_event(handle);
//     handle.eds.event.fields.et = ET_READ;
//     handle.eds.event.fields.pt = PT_UART;
//     handle.timerPreset = 4;
//     handle.persistent = true;
//     create_event(handle);

    handle_events();
    timer_tick();
    timer_tick();
    timer_tick();
    timer_tick();
    timer_tick();
    handle_events();
  
    Event *event0 = get_system_event(0);
    
    printf("MAIN\r\n");
    printf("handle address %p\r\n", &event0->handle);
    printf("handle.eds.event.value: %d\r\n", event0->handle.eds.event.value);
    printf("handle.timerPreset: %d\r\n", event0->handle.timerPreset);
    return 0; 
}

