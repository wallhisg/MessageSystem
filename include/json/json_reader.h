#ifndef JSON_READ_H
#define JSON_READ_H

#include "json_parser_object.h"

typedef void* (ToKStart)(const char, void *);

char json_object_read_description(Buffer *inBuff);

char json_read_description(Buffer *inBuff, void *tokStart);


#endif  //  JSON_READ_H
