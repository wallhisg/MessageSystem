#include <stdio.h>
#include <event/handle.h>

int main()
{
    printf("TEST_EVENT_DESCRIPTION\r\n");
    
    EventDescription eds;
    
    eds.event.fields.et = ET_READ;
    eds.event.fields.pt = PT_GPIO;
    
    printf("eds.event.fields.et: %d\r\n", eds.event.fields.et);
    printf("eds.event.fields.pt: %d\r\n", eds.event.fields.pt);
    printf("eds.event.value: %d\r\n", eds.event.value);
    printf("Size of EventDescription: %lu\r\n", sizeof(EventDescription));
    return 0; 
}
