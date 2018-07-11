#include <Message/Endpoint/Endpoint.h>


static Endpoint endpoint;

void endpoint_init()
{
    endpoint.type = UNDEFINE;
    
    // init gpio endpoint
    endpoint.gpio.handleEvent.read = (void*)gpio_read_pin_state;
    endpoint.gpio.handleEvent.set = (void*)gpio_set_pin;
    endpoint.gpio.handleEvent.clear = (void*)gpio_clear_pin;
    
}

EndpointPtr get_endpoint()
{
    return &endpoint;
}
