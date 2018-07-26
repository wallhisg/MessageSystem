#include <event/event_manager.h>
#include <driver/driver.h>

void event_table_read(Handle *handle);
void event_table_write(Handle *handle);
void event_table_recv(Handle *handle);
void event_table_send(Handle *handle);
void event_table_parser(Handle *handle);

void handle_events_by_description(Handle *handle)
{
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
        case ET_PARSER:
        {
            event_table_parser(handle);
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
            gpio_read(&handle->ad);
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
            gpio_write(&handle->ad);
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

void event_table_parser(Handle *handle)
{
    EventDescription *eds = &handle->eds;

    switch (eds->event.fields.pt) {
        case PT_RX_UART:
        {
            uart_rx_parser();
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
    EventDescription *eds = &handle->eds;
    
    // Loop continuously if persistent is TRIBOOL_INDETERMINATE
    if(handle->persistent != TRIBOOL_INDETERMINATE)
    {
        if(eds->revent.value)
        {
        eds->event .value= eds->revent.value;
        eds->revent.value = 0;
        handle->persistent = TRIBOOL_TRUE;
        }
        else
        {
            eds->event.value = 0;
            eds->revent.value = 0;
            handle->persistent = TRIBOOL_FALSE;
        }
    }
    else 
    {
        // Reload event
        if(eds->revent.value)
        {
            eds->event .value= eds->revent.value;
        }
    }
}


