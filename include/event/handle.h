#ifndef HANDLE_H
#define HANDLE_H

#include <stdbool.h>
#include <system/system.h>

//  Define file table - Operations
#define ET_NONE     0x00
#define ET_READ     0x01
#define ET_WRITE    0x02
#define ET_RECV     0x03
#define ET_SEND     0x04
#define ET_PARSER   0x05

//  Define inode table - Peripheral
#define PT_NONE     0x00
#define PT_GPIO     0x01
#define PT_ADC      0x02
#define PT_PWM      0x03
#define PT_RX_UART  0x04
#define PT_TX_UART  0x05
#define PT_SPI      0x06
#define PT_I2C      0x07

typedef enum {
    POLLERR, POLLHUP,
    POLLNVAL, POLLVAL,
    POLLIN, POLLOUT
} EventPoll;

typedef struct {
    uint8_t pt;     //  peripheral table
    uint8_t et;     //  event table
} EventDescriptionBitFields;

typedef union {
    EventDescriptionBitFields fields;               
    uint16_t value;
} EventDescriptionField;

typedef struct {
    EventDescriptionField event;    //  requested events
    EventDescriptionField revent;   //  returned events
} EventDescription;

/*
 * persistent:
 *  - TRIBOOL_TRUE, TRIBOOL_FALSE create loop with conditions
 *  - TRIBOOL_INDETERMINATE create loops continuously.
 */
typedef struct {
    AddressValue ad;
    EventDescription eds;
    TriBool persistent;
    uint16_t timerPreset;
} Handle;

#endif  //  HANDLE_H
