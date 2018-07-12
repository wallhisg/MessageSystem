#ifndef ROUTER_H
#define ROUTER_H

#include <system/system.h>
#include <message/endpoint/endpoint.h>
#include <message/channel/channel.h>

void regist_message(EndpointType type, void *message);
void unregist_message(EndpointType type, void *message);

#endif  //  ROUTER_H
