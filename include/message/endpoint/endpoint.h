#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <system/system.h>
#include <message/message.h>
#include <driver/gpio.h>

typedef struct {
//     EndpointType type;
    void* instance;
} Endpoint, *EndpointPtr;

void endpoint_init();
EndpointPtr get_endpoint();

void create_gpio_message();
void read_gpio_message();
void write_gpio_message();

#endif  //  ENDPOINT_H
