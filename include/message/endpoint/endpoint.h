#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <system/system.h>
#include <driver/gpio.h>


typedef enum {
    UNDEFINE,
    UART,
    GPIO,
    ADC
} endpoint_type;

typedef struct {
    endpoint_type type;
    gpio_t gpio;
} endpoint_t, *endpoint_ptr;

void endpoint_init();
endpoint_ptr get_endpoint();

#endif  //  ENDPOINT_H
