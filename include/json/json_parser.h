#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <stdbool.h>
#include <ctype.h>
#include <debug.h>
#include <json/json.h>
#include <driver/ring_buffer.h>

int json_parser(JsonSchema *jsonSchema, BufferPtr uartRxBuffer);
JsonConsume consume_char(char c, JsonConsume jsonConsume);


#endif // JSON_PARSER_H
