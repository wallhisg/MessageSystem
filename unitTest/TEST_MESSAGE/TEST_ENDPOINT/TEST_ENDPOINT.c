#include <stdio.h>
#include <message/endpoint/endpoint.h>

int main()
{
    printf("----- TEST ENDPOINT -----\r\n");
    endpoint_init();
    
    endpoint_ptr ep = get_endpoint();
    
    address_value_t av;
    av.address = 12;
    av.value = 100;
    ep->gpio.addressValue = av;
    ep->gpio.handleEvent.clear(&ep->gpio.addressValue);
    
    return 0; 
}

