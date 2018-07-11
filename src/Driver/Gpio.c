#include <Driver/Gpio.h>


void gpio_read_pin_state(void *instance)
{
    printf("gpio_read_pin_state\r\n");
    AddressValuePtr addressValue = instance;
    printf("address %d\r\n", addressValue->address);
    printf("bit %d\r\n", addressValue->value);
}

void gpio_set_pin(void *instance)
{
    printf("gpio_set_pin\r\n");
    AddressValuePtr addressValue = instance;
    printf("address %d\r\n", addressValue->address);
    printf("bit %d\r\n", addressValue->value);
}

void gpio_clear_pin(void *instance)
{
    printf("gpio_clear_pin\r\n");
    AddressValuePtr addressValue = instance;
    printf("address %d\r\n", addressValue->address);
    printf("bit %d\r\n", addressValue->value);
}

void gpio_toggle_pin(void *instance)
{
    printf("gpio_toggle_pin\r\n");
    AddressValuePtr addressValue = instance;
    printf("address %d\r\n", addressValue->address);
    printf("bit %d\r\n", addressValue->value);
}

void gpio_enable_pin(void *instance)
{
    printf("gpio_enable_pin\r\n");
    AddressValuePtr addressValue = instance;
    printf("address %d\r\n", addressValue->address);
    printf("bit %d\r\n", addressValue->value);
}

void gpio_disable_pin(void *instance)
{
    printf("gpio_disable_pin\r\n");
    AddressValuePtr addressValue = instance;
    printf("address %d\r\n", addressValue->address);
    printf("bit %d\r\n", addressValue->value);
}

