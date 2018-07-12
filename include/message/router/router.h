#ifndef ROUTER_H
#define ROUTER_H

#include <system/system.h>
#include <message/endpoint/endpoint.h>
#include <message/channel/channel.h>

void router_init();
void regist_message(MessageHandle handle, void *message);
void unregist_message(MessageHandle handle, void *message);

#endif  //  ROUTER_H
