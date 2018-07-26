#include <system/system.h>
#include <driver/driver.h>
#include <json/json.h>
#include <message/message.h>
#include <message/endpoint/endpoint.h>
#include <message/channel/channel.h>
#include <message/router/router.h>


void system_init()
{
    driver_init();
    json_init();
    event_init();
    
    endpoint_init();
    channel_init();
    router_init();
}
