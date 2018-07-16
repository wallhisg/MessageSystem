#ifndef HANDLE_H
#define HANDLE_H

#include <stdbool.h>
#include <system/system.h>

// POLLIN
#define EVENTS                  0x00
#define EVENT_WRITE_REGISTER    0x01
#define EVENT_WRITE_GPIO        0x02

// POLLOUT
#define REVENTS                 0x00
#define REVENT_READ_REGISTER    0x01
#define REVENT_READ_GPIO        0x02
#define REVENT_READ_ADC         0x03

// typedef uint16_t    EventID;

typedef union {
    struct {
        uint8_t events;
        uint8_t revents;
    } fd; 
    uint16_t id;
} EventId;

typedef struct {
    uint16_t preset;
    uint16_t counter;
} Timer;

typedef struct {
    AddressValue addressValue;
    EventId eventId;
    bool persistent;
    Timer timer;
} Handle;

#endif  //  HANDLE_H
