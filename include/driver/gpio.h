#ifndef GPIO_H
#define GPIO_H

#include <system/system.h>

typedef struct {
    uint8_t address;
    uint8_t value;
} address_value_t, *address_value_ptr;

typedef struct {
    handle_event_func read;
    handle_event_func write;
    handle_event_func toggle;
    handle_event_func set;
    handle_event_func clear;
    handle_event_func enable;
    handle_event_func disable;
} gpio_function;

typedef struct {
    gpio_function handleEvent;
    address_value_t addressValue;
} gpio_t;

void gpio_set_pin(void *instance);
void gpio_clear_pin(void *instance);
void gpio_read_pin_state(void *instance);
void gpio_toggle_pin(void *instance);
void gpio_enable_pin(void *instance);
void gpio_disable_pin(void *instance);


#endif  //  GPIO_H
