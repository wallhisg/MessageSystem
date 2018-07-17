#include <stdio.h>
#include <event/handle.h>

int main()
{
    printf("Message system\r\n");
    EventFd eventId = {0};
    eventId.id = (REVENT_READ_ADC << 8) | EVENT_WRITE_REGISTER;
    
    printf("EventID: %x\n", eventId.id);
    printf("Events: %x\n", eventId.fd.events);
    printf("Revents: %x\n", eventId.fd.revents);
    
    return 0; 
}
