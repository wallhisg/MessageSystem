#include <stdio.h>
#include <Message/Endpoint/Endpoint.h>

int main()
{
    printf("----- TEST ENDPOINT -----\r\n");
    endpoint_init();
    
    EndpointPtr ep = get_endpoint();
    
    AddressValue av;
    av.address = 12;
    av.value = 100;
    ep->gpio.addressValue = av;
    ep->gpio.handleEvent.clear(&ep->gpio.addressValue);
    
    return 0; 
}

