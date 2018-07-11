#include <message/endpoint/endpoint.h>


static endpoint_t endpoint;

void endpoint_init()
{
    endpoint.type = UNDEFINE;
    
    // init gpio endpoint
    endpoint.gpio.handleEvent.read = (void*)gpio_read_pin_state;
    endpoint.gpio.handleEvent.set = (void*)gpio_set_pin;
    endpoint.gpio.handleEvent.clear = (void*)gpio_clear_pin;
    
}

endpoint_ptr get_endpoint()
{
    return &endpoint;
}
