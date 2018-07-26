#ifndef JSON_H
#define JSON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <system/system.h>
#include <driver/ring_buffer.h>

#define LF      0x0A    //  '\n' - New Line
#define CR      0x0D    //  '\r' - Enter

// SYSTEM MESSAGE
// define TYPE JSON
#define MAX_NO_OF_JSON_OBJECT   0x08
#define MSG_TYPE_JSON           0x80
#define MSG_TYPE_JSON_STRING    0x81
#define MSG_TYPE_JSON_OBJECT    0x82
#define MSG_TYPE_JSON_ARRAY     0x83

#define MAX_NO_OF_JSON_BUFFER       64
#define JSON_OBJECT_KEY_LENGTH      64
#define JSON_OBJECT_VALUE_LENGTH    64

typedef enum {
    ERROR_NONE      = 0,
    ERROR_SYNTAX    = 1,
    ERROR_UNDEFINED = 2
} JSonError;

typedef enum {
    JSON_TYPE_UNDEFINED,
    JSON_TYPE_STRING,
    JSON_TYPE_OBJECT,
    JSON_TYPE_ARRAY
} JsonType;

typedef enum {
    JSON_OBJECT_INDERERMINATE,
    JSON_OBJECT_NEW,
    JSON_OBJECT_KEY,
    JSON_OBJECT_KEY_NEW,
    JSON_OBJECT_KEY_END,
    JSON_OBJECT_VALUE,
    JSON_OBJECT_END
} JsonObjectState;

// six struct tokens
typedef enum {
    JTK_L_CURLY,        //  {
    JTK_R_CURLY,        //  }
    JTK_COLON,          //  :
    JTK_COMMA,          //  ,
    JTK_L_BRACKET,      //  [
    JTK_R_BRACKET,      //  ]
    // extra token
    JEX_LETTER_START,   //
    JEX_DQ_MARK,        //  "
    JEX_LETTER,         //  letter
    JEX_SPACE,          //  space
} JsonToken;

typedef struct {
    JsonToken tok;
    TriBool tribool;
    JsonType type;
} JSonTupleFlag;

typedef char *JsonString;

typedef struct {
    char key[JSON_OBJECT_KEY_LENGTH];
    char value[JSON_OBJECT_VALUE_LENGTH];
} JsonValue, *JsonValuePtr;

typedef struct {
    JsonValue keyValue;
    bool isUsed;
} JsonObject, *JsonObjectPtr;

typedef struct {
    JsonObjectPtr jsonObj;
    size_t size;
} JsonObjectArray, *JsonObjectArrayPtr;

typedef struct JsonConsume{
    bool isObjects;
    JsonObjectState state;
    uint8_t tokCounter;
    TriBool tribool;
    JsonType type;
    struct JsonConsume (*nextTok)(const char, struct JsonConsume);
} JsonConsume;

void json_init();
void write_one_byte_to_json_buffer(char byte);
char read_one_byte_from_json_buffer();

Buffer *get_json_buffer();

void clear_buffer(char *buff, size_t size);

bool is_tok_letter(const char c);

bool insert_json_object(JsonValue keyValue);
JsonValue *get_json_object();

int find_free_json_object_slot();
int get_no_of_json_object();
void clear_json_object(JsonValue *keyValue);
bool is_json_object_empty(JsonObject jsonObj);
void json_consume_init(JsonConsume *jsonConsume);

#endif // JSON_H
