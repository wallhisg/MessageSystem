#include <stdio.h>
#include <event/handle.h>
#include <event/event.h>
#include <event/event_manager.h>


int main()
{
    printf("TEST_EVENT_DESCRIPTION\r\n");
    
    Handle handle = {0};
    handle.eds = event_description(ET_SEND, PT_TX_UART, ET_READ, PT_GPIO);
    handle.ad.address = 0x55;
    handle.ad.value = 0xAA;

    printf("BEFORE\r\n");
    printf("handle.eds.event.fields.et: %d\r\n", handle.eds.event.fields.et);
    printf("handle.eds.event.fields.pt: %d\r\n", handle.eds.event.fields.pt);

    printf("handle.eds.revent.fields.et: %d\r\n", handle.eds.revent.fields.et);
    printf("handle.eds.revent.fields.pt: %d\r\n", handle.eds.revent.fields.pt);

    printf("handle.buff.address: %d\r\n", handle.ad.address);
    printf("handle.buff.value: %d\r\n", handle.ad.value);

    handle_events_by_description(&handle);
    handle_revent_by_description(&handle);

    printf("AFTER\r\n");
    printf("handle.eds.event.fields.et: %d\r\n", handle.eds.event.fields.et);
    printf("handle.eds.event.fields.pt: %d\r\n", handle.eds.event.fields.pt);

    printf("handle.eds.revent.fields.et: %d\r\n", handle.eds.revent.fields.et);
    printf("handle.eds.revent.fields.pt: %d\r\n", handle.eds.revent.fields.pt);

    printf("handle.buff.address: %d\r\n", handle.ad.address);
    printf("handle.buff.value: %d\r\n", handle.ad.value);
    return 0; 
}
