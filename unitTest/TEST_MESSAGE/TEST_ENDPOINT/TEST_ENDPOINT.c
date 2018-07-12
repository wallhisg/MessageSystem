#include <stdio.h>
#include <system/system.h>
#include <message/endpoint/endpoint.h>

int main()
{
    printf("----- TEST ENDPOINT -----\r\n");
    system_init();
    
    create_gpio_message();
    
    return 0; 
}

