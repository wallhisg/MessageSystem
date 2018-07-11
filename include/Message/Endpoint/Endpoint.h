#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <System/System.h>
#include <Driver/Gpio.h>


typedef enum {
    UNDEFINE,
    UART,
    GPIO,
    ADC
} EndpointType;

typedef struct {
    EndpointType type;
    Gpio gpio;
} Endpoint, *EndpointPtr;

void endpoint_init();
EndpointPtr get_endpoint();

#endif  //  ENDPOINT_H
