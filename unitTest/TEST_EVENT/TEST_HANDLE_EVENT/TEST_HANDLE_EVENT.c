#include <stdio.h>
#include <system/system.h>
#include <event/handle.h>
#include <event/event.h>
#include <event/event_loop.h>
#include <event/reactor.h>

#include "TEST_HANDLE.h"
#include "TEST_HANDLE_UART.h"

#ifndef LOOP
#define LOOP    10
#endif

int main()
{
    printf("----- TEST_HANDLE_EVENT -----\r\n");
    system_init();

//    TEST_HANDLE_EVENT();
//    TEST_HANDLE_EVENT_WITH_PERSISTENT();

    TEST_UART_RX();
    return 0; 
}

