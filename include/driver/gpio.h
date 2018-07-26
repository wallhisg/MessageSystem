#ifndef GPIO_H
#define GPIO_H

#include <system/config.h>
#include <system/system.h>
#include <event/handle.h>


// typedef struct {
// 
//     gpio_function handleEvent;
//     address_value_t addressValue;
// } gpio_t;

void gpio_set_pin(void *instance);
void gpio_clear_pin(void *instance);
void gpio_read_pin_state(void *instance);
void gpio_toggle_pin(void *instance);
void gpio_enable_pin(void *instance);
void gpio_disable_pin(void *instance);
void gpio_read(AddressValue *eventBuff);
void gpio_write(AddressValue *eventBuff);

#endif  //  GPIO_H
