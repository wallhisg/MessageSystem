#include <event/event_manager.h>

void event_table_read(Handle *handle);
void event_table_write(Handle *handle);
void event_table_recv(Handle *handle);
void event_table_send(Handle *handle);

void handle_events_by_description(Handle *handle)
{
    printf("handle_events_by_description\r\n");
    printf("handle->eds.event.fields.et: %d\r\n", handle->eds.event.fields.et);

    EventDescription *eds = &handle->eds;

    switch (eds->event.fields.et) {
        case ET_READ:
        {
            event_table_read(handle);
            break;
        }
        case ET_WRITE :
        {
            event_table_write(handle);
            break;
        }
        case ET_RECV :
        {
            event_table_recv(handle);
            break;
        }
        case ET_SEND :
        {
            event_table_send(handle);
            break;
        }
        default:
            break;
    }

}

void event_table_read(Handle *handle)
{
    EventDescription *eds = &handle->eds;

    switch (eds->event.fields.pt) {
        case PT_GPIO:
        {
            gpio_read(&handle->buff);
            break;
        }
        case PT_ADC:
        {
            break;
        }
        case PT_PWM:
        {
            break;
        }
        default:
            break;
    }

}

void event_table_write(Handle *handle)
{
    EventDescription *eds = &handle->eds;

    switch (eds->event.fields.pt) {
        case PT_GPIO:
        {
            break;
        }
        case PT_PWM:
        {
            break;
        }
        default:
            break;
    }
}

void event_table_recv(Handle *handle)
{
    EventDescription *eds = &handle->eds;

    switch (eds->event.fields.pt) {
        case PT_GPIO:
        {
            break;
        }
        case PT_PWM:
        {
            break;
        }
        default:
            break;
    }
}

void event_table_send(Handle *handle)
{
    EventDescription *eds = &handle->eds;

    switch (eds->event.fields.pt) {
        case PT_GPIO:
        {
            break;
        }
        case PT_PWM:
        {
            break;
        }
        default:
            break;
    }
}

void handle_revent_by_description(Handle *handle)
{
    printf("handle_revent_by_description\r\n");

    EventDescription *eds = &handle->eds;

    if(eds->revent.value)
    {
       eds->event .value= eds->revent.value;
       eds->revent.value = 0;
       handle->persistent = true;
    }
    else
    {
        eds->event.value = 0;
        eds->revent.value = 0;
        handle->persistent = false;
    }
}
