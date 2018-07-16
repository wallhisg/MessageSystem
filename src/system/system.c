#include <system/system.h>
#include <message/message.h>
#include <message/endpoint/endpoint.h>
#include <message/channel/channel.h>
#include <message/router/router.h>


void system_init()
{
//     system_event_init();
    
    endpoint_init();
    channel_init();
    router_init();
}
