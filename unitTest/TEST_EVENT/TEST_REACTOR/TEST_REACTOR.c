#include <stdio.h>
#include <system/system.h>
#include <event/handle.h>
#include <event/event.h>


int main()
{
    printf("----- TEST_EVENT_REACTOR -----\r\n");
    system_init();
    
    Handle handle = {0};

//     handle.event.value = (REVENT_READ_ADC << 8) | EVENT_WRITE_REGISTER;
    handle.eds.event.fields.et = ET_READ;
    handle.eds.event.fields.pt = PT_UART;
    handle.timerPreset = 10;
    handle.persistent = false;
    handle.buff.address = 0x55;
    handle.buff.value = 0xAA;

    create_event(handle);
    handle.persistent = true;
    create_event(handle);

    Event *event0 = get_system_event(0);
    Event *event1 = get_system_event(1);
    printf("----- EVENT 0 INIT -----\r\n");

    printf("event0->handle.fd.id: %d\r\n", event0->handle.eds.event.value);
    printf("event0->handle.persistent: %d\r\n", event0->handle.persistent);
    printf("event0->handle.timerPreset: %d\r\n", event0->handle.timerPreset);

    printf("----- EVENT 0 REMOVE -----\r\n");
    event0->notifier.onEventClosed(&event0->eventHandler);
    printf("event0->handle.fd.id: %d\r\n", event0->handle.eds.event.value);
    printf("event0->handle.persistent: %d\r\n", event0->handle.persistent);
    printf("event0->handle.timerPreset: %d\r\n", event0->handle.timerPreset);

    printf("----- EVENT 1 INIT -----\r\n");

    printf("event1->handle.fd.id: %d\r\n", event1->handle.eds.event.value);
    printf("event1->handle.persistent: %d\r\n", event1->handle.persistent);
    printf("event1->handle.timerPreset: %d\r\n", event1->handle.timerPreset);

    printf("----- EVENT 1 REMOVE -----\r\n");
    event1->notifier.onEventClosed(&event1->eventHandler);
    printf("event1->handle.fd.id: %d\r\n", event1->handle.eds.event.value);
    printf("event1->handle.persistent: %d\r\n", event1->handle.persistent);
    printf("event1->handle.timerPreset: %d\r\n", event1->handle.timerPreset);



    return 0; 
}

