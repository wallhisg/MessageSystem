#include <message/endpoint/endpoint.h>


static Endpoint endpoint;

void endpoint_init()
{
//     endpoint.type = UNDEFINE;
    
    // init gpio endpoint
//     endpoint.gpio.handleEvent.read = (void*)gpio_read_pin_state;
//     endpoint.gpio.handleEvent.set = (void*)gpio_set_pin;
//     endpoint.gpio.handleEvent.clear = (void*)gpio_clear_pin;
    
}

EndpointPtr get_endpoint()
{
    return &endpoint;
}

void create_gpio_message()
{
    MessageHandle message;
    message.endpoint = ENDPOINT_GPIO;
    message.type = COMMAND;
    message.router = CONTENT_BASED_ROUTER;
    message.channel = POINT_TO_POINT;

    create_message(message, NULL);
}

void read_gpio_message()
{

}

void write_gpio_message()
{

}
