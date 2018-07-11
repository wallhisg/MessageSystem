#ifndef MESSAGE_H
#define MESSAGE_H

#include <system/system.h>
#include <message/endpoint/endpoint.h>

typedef struct {
    void *instance;
    endpoint_type type;
    bool isUsed;
} message_t;


#endif  //  MESSAGE_H
