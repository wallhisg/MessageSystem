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

//  Define file table - Operations
#define ET_NONE     0b000
#define ET_READ     0b001
#define ET_WRITE    0b010
#define ET_RECV     0b011
#define ET_SEND     0b100

//  Define inode table - Peripheral
#define PT_NONE     0b00000
#define PT_GPIO     0b00001
#define PT_ADC      0b00010
#define PT_PWM      0b00011
#define PT_UART     0b00100
#define PT_SPI      0b00101
#define PT_I2C      0b00111

typedef enum {
    POLLERR, POLLHUP,
    POLLNVAL, POLLVAL,
    POLLIN, POLLOUT
} EventPoll;

typedef struct {
    uint8_t pt : 5;     //  peripheral table
    uint8_t et : 3;     //  event table
} EventDescriptionBitFields;

typedef union {
    EventDescriptionBitFields fields;               
    uint8_t value;
} EventDescriptionField;

typedef struct {
    EventDescriptionField event;    //  requested events
    EventDescriptionField revent;   //  returned events
} EventDescription;

typedef struct {
    EventBuff fileData;
    EventDescription eds;
    bool persistent;
    uint16_t timerPreset;
} Handle;

#endif  //  HANDLE_H
