#include <stdio.h>
#include <system/system.h>
#include <event/handle.h>
#include <event/event.h>
#include <event/reactor_event_loop.h>
#include <event/poll_reactor.h>

int main()
{
    printf("----- TEST_HANDLE_EVENT -----\r\n");
    system_init();
    
    Handle handle = {0};

    handle.fd.id = (REVENT_READ_ADC << 8) | EVENT_WRITE_REGISTER;
    handle.timerPreset = 3;
    handle.persistent = true;
    handle.addressValue.address = 0x55;
    handle.addressValue.value = 0xAA;

    create_event(handle);
    handle.fd.id = (REVENT_READ_ADC << 8) | EVENT_WRITE_REGISTER;
    handle.timerPreset = 4;
    handle.persistent = true;
    create_event(handle);

    handle_events();
    timer_tick();
    timer_tick();
    timer_tick();
    timer_tick();
    timer_tick();
    handle_events();
    handle_events();
    handle_events();
    timer_tick();
    timer_tick();
    timer_tick();
    timer_tick();
    timer_tick();    
    handle_events();
    handle_events();    
    return 0; 
}

