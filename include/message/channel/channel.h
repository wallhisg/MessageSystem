#ifndef CHANNEL_H
#define CHANNEL_H

#include <system/system.h>
#include <message/endpoint/endpoint.h>
#include "gpio_channel.h"

#define MAX_NO_OF_GPIO_MESSAGE  8

void channel_init();

void regist_message(void *channel, endpoint_type type, void *message);

#endif  //  CHANNEL_H

