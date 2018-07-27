#include <string.h>
#include <json/json_parser_object.h>

JsonConsume tok_obj_letter_start(const char c, JsonConsume objConsume);
JsonConsume tok_obj_dq_mark(const char c, JsonConsume objConsume);
JsonConsume tok_obj_colon(const char c, JsonConsume objConsume);
JsonConsume tok_obj_comma(const char c, JsonConsume objConsume);
JsonConsume tok_obj_l_curly(const char c, JsonConsume objConsume);
JsonConsume tok_obj_r_curly(const char c, JsonConsume objConsume);
JsonConsume tok_obj_l_bracket(const char c, JsonConsume objConsume);
JsonConsume tok_obj_r_bracket(const char c, JsonConsume objConsume);
JsonConsume tok_obj_letter(const char c, JsonConsume objConsume);
JsonObjectState next_json_object_state(JsonObjectState objState);

bool json_parser_object(Buffer *inBuff)
{
    bool result = false;

    JsonConsume objConsume;
    json_consume_init(&objConsume);
    objConsume.nextTok = tok_obj_letter_start;
    objConsume.state = JSON_OBJECT_NEW;

    JsonValue keyValue;
    uint8_t keyIdx = 0;
    uint8_t valIdx = 0;

    char byte = ' ';

    while((inBuff->status != RING_STATUS_EMPTY) && (byte != LF))
    {
        byte = buffer_read_one_byte(inBuff);
        objConsume = consume_object(byte, objConsume);

        if(objConsume.state == JSON_OBJECT_KEY)
        {
            memset(keyValue.key, 0, JSON_OBJECT_KEY_LENGTH * sizeof(char));
            memset(keyValue.value, 0, JSON_OBJECT_VALUE_LENGTH * sizeof(char));

            keyIdx = 0;
            valIdx = 0;
        }
        else if(objConsume.state == JSON_OBJECT_VALUE_END)
        {
            keyValue.key[keyIdx] = '\0';
            keyValue.value[valIdx] = '\0';
            if(!insert_json_object(keyValue))
            {
                // if false -> warning
                objConsume.tribool = TRIBOOL_FALSE;
                printf("ERROR\r\n");
                break;
            }
        }

        if ((objConsume.tribool == TRIBOOL_TRUE) && (objConsume.state == JSON_OBJECT_KEY_BEGIN))
        {
//             printf("KEY: byte: %c\r\n", byte);
//            debug_message("KEY: byte: %c\r\n", byte);
            keyValue.key[keyIdx++] = byte;
        }
        else if ((objConsume.tribool == TRIBOOL_TRUE) && (objConsume.state == JSON_OBJECT_VALUE_BEGIN))
        {
//             printf("VALUE: byte: %c\r\n", byte);
//            debug_message("VALUE: byte: %c\r\n", byte);
            keyValue.value[valIdx++] = byte;
        }
    }

    if(objConsume.tribool == TRIBOOL_TRUE)
        result = true;
    else {
        result = false;
    }

//    debug_message("result %lu\r\n", result);
    return result;
}

JsonConsume consume_object(const char c, JsonConsume objConsume)
{
    JsonConsume consume;
//    printf("TRUOC - objConsume.state: %d\r\n", objConsume.state);
    consume = objConsume.nextTok(c, objConsume);
//    printf("\r\b");
//    printf("Char: %c\r\n", c);
//    printf("SAU - objConsume.state: %d\r\n", consume.state);
//    printf("tribool: %d\r\n", objConsume.tribool);
//    debug_message("consume_char: %c : >> ", c);
    return consume;
}

JsonConsume tok_obj_letter_start(const char c, JsonConsume objConsume)
{
    debug_message("tok_obj_letter_start\r\n");
    JsonConsume consume = objConsume;

    switch (c) {
        case '\"' :
        {
            consume.nextTok = tok_obj_dq_mark;
            consume.tribool = TRIBOOL_INDETERMINATE;
            consume.state = next_json_object_state(consume.state);
            break;
        }
        default:
        {
            consume.tribool = TRIBOOL_FALSE;
            break;
        }
    }

    return consume;
}

// CASE "
JsonConsume tok_obj_dq_mark(const char c, JsonConsume objConsume)
{
    debug_message("tok_obj_dq_mark");
    JsonConsume consume = objConsume;

    switch (c) {
        case ':' :
        {
            consume.nextTok = tok_obj_colon;
            if(consume.isObjects)
            {
                consume.tribool = TRIBOOL_TRUE;
            }
            else
            {
                consume.state = next_json_object_state(consume.state);
                consume.tribool = TRIBOOL_INDETERMINATE;
            }
            break;
        }
        case ',':
        {
            consume.nextTok = tok_obj_comma;
            if(consume.isObjects)
            {
                consume.tribool = TRIBOOL_TRUE;
            }
            else
            {
                consume.state = next_json_object_state(consume.state);
                consume.tribool = TRIBOOL_INDETERMINATE;
            }
            break;
        }
        case '}':
        {
            consume.nextTok = tok_obj_r_curly;
            consume.state = next_json_object_state(consume.state);
            consume.tribool = TRIBOOL_INDETERMINATE;
            consume.isObjects = false;
            break;
        }
        case ']' :
        {
            consume.nextTok = tok_obj_r_bracket;
            consume.state = next_json_object_state(consume.state);
            consume.tribool = TRIBOOL_INDETERMINATE;
            consume.isObjects = false;
            break;
        }
        case '\0':
        case '\r':
        case '\n':
        {
            consume.tribool = TRIBOOL_TRUE;
            consume.state = JSON_OBJECT_END;
            break;
        }
        default:
        {
            if(isalpha(c) || isdigit(c))
            {
                consume.nextTok = tok_obj_letter;
                consume.tribool = TRIBOOL_TRUE;
                if(consume.state == JSON_OBJECT_KEY)
                    consume.state = JSON_OBJECT_KEY_BEGIN;
                else if(consume.state == JSON_OBJECT_VALUE)
                    consume.state = JSON_OBJECT_VALUE_BEGIN;
            }
            else {
                consume.tribool = TRIBOOL_FALSE;
            }


            break;
        }
    }

    return consume;
}

// CASE :
JsonConsume tok_obj_colon(const char c, JsonConsume objConsume)
{
    debug_message("tok_obj_colon");

    JsonConsume consume = objConsume;

    switch (c) {
        case '\"' :
        {
            consume.nextTok = tok_obj_dq_mark;

            if(consume.isObjects)
            {
                consume.tribool = TRIBOOL_TRUE;
            }
            else
            {
                consume.tribool = TRIBOOL_INDETERMINATE;
            }
            break;
        }
        case '{':
        {
            consume.nextTok = tok_obj_l_curly;
            consume.isObjects = true;
            consume.state = next_json_object_state(consume.state);
            consume.tribool = TRIBOOL_INDETERMINATE;
            break;
        }
        case '[' :
        {
            consume.nextTok = tok_obj_l_bracket;
            consume.isObjects = true;
            consume.state = next_json_object_state(consume.state);
            consume.tribool = TRIBOOL_INDETERMINATE;
            break;
        }
        default:
        {
            consume.tribool = TRIBOOL_FALSE;
            break;
        }
    }

    return consume;
}

// CASE ,
JsonConsume tok_obj_comma(const char c, JsonConsume objConsume)
{
    debug_message("tok_obj_comma");

    JsonConsume consume = objConsume;

    switch (c) {
        case '\"' :
        {
            consume.nextTok = tok_obj_dq_mark;
            if(consume.isObjects)
            {
                consume.tribool = TRIBOOL_TRUE;
            }
            else
            {
                consume.state = next_json_object_state(consume.state);
                consume.tribool = TRIBOOL_INDETERMINATE;
            }
            break;
        }
        default:
        {
            consume.tribool = TRIBOOL_FALSE;
            break;
        }
    }

    return consume;
}

// CASE {
JsonConsume tok_obj_l_curly(const char c, JsonConsume objConsume)
{
    debug_message("tok_obj_l_curly");

    JsonConsume consume = objConsume;

    switch (c) {
        case '\"' :
        {
            consume.nextTok = tok_obj_dq_mark;
            if(consume.isObjects)
            {
                consume.tribool = TRIBOOL_TRUE;
            }
            break;
        }
        default:
        {
            consume.tribool = TRIBOOL_FALSE;
            break;
        }
    }

    return consume;
}

// CASE }
JsonConsume tok_obj_r_curly(const char c, JsonConsume objConsume)
{
    debug_message("tok_obj_r_curly");

    JsonConsume consume = objConsume;

    switch (c) {
        case ',' :
        {
            consume.nextTok = tok_obj_comma;
            consume.isObjects = false;
            consume.tribool = TRIBOOL_INDETERMINATE;
            consume.state = next_json_object_state(consume.state);
            break;
        }
        case '\0':
        case '\r':
        case '\n':
        {
            consume.tribool = TRIBOOL_TRUE;
            consume.state = JSON_OBJECT_INDERERMINATE;
            break;
        }
        default:
        {
            consume.tribool = TRIBOOL_FALSE;
            break;
        }
    }

    return consume;
}

//  CASE [
JsonConsume tok_obj_l_bracket(const char c, JsonConsume objConsume)
{
    debug_message("tok_obj_l_bracket");

    JsonConsume consume = objConsume;

    switch (c) {
        case '\"' :
        {
            consume.nextTok = tok_obj_dq_mark;
            if(consume.isObjects)
            {
                consume.tribool = TRIBOOL_TRUE;
            }
            break;
        }
        default:
        {
            consume.tribool = TRIBOOL_FALSE;
            break;
        }
    }

    return consume;
}

//  CASE ]
JsonConsume tok_obj_r_bracket(const char c, JsonConsume objConsume)
{
    debug_message("tok_obj_r_bracket");

    JsonConsume consume = objConsume;

    switch (c) {
        case '\0':
        case '\r':
        case '\n':
        {
            consume.tribool = TRIBOOL_TRUE;
//             consume.state = JSON_OBJECT_INDERERMINATE;
            consume.state = JSON_OBJECT_END;
            break;
        }
        case ',' :
        {
            consume.nextTok = tok_obj_comma;
            consume.isObjects = false;
            consume.tribool = TRIBOOL_INDETERMINATE;
            consume.state = next_json_object_state(consume.state);
            break;
        }
        case '}':
        {
            consume.nextTok = tok_obj_r_curly;
            consume.isObjects = false;
            consume.tribool = TRIBOOL_INDETERMINATE;
            consume.state = next_json_object_state(consume.state);
            break;
        }
        default:
        {
            consume.tribool = TRIBOOL_FALSE;
            break;
        }
    }

    return consume;
}

// CASE A -> Z, 0 -> 1
JsonConsume tok_obj_letter(const char c, JsonConsume objConsume)
{
    debug_message("tok_obj_letter");
    JsonConsume consume = objConsume;

    switch (c) {
        case '\"' :
        {
            consume.nextTok = tok_obj_dq_mark;
            if(consume.isObjects)
            {
                consume.tribool = TRIBOOL_TRUE;
            }
            else
            {
                consume.state = next_json_object_state(consume.state);
            }
            break;
        }
        default:
        {
            if (isalpha(c) || isdigit(c))
            {
                consume.nextTok = tok_obj_letter;
                consume.tribool = TRIBOOL_TRUE;
            }
            else
                consume.tribool = TRIBOOL_FALSE;

            break;
        }
    }

    return consume;
}

JsonObjectState next_json_object_state(JsonObjectState objState)
{
    JsonObjectState state = objState;
    switch (state)
    {
        case JSON_OBJECT_INDERERMINATE :
            state = JSON_OBJECT_NEW;
            break;
        case JSON_OBJECT_NEW:
            state = JSON_OBJECT_KEY;
            break;
        case JSON_OBJECT_KEY:
            state = JSON_OBJECT_KEY_BEGIN;
            break;            
        case JSON_OBJECT_KEY_BEGIN:
            state = JSON_OBJECT_KEY_END;
            break;
        case JSON_OBJECT_KEY_END:
            state = JSON_OBJECT_VALUE;
            break;
        case JSON_OBJECT_VALUE:
            state = JSON_OBJECT_VALUE_BEGIN;
            break;
        case JSON_OBJECT_VALUE_BEGIN:
            state = JSON_OBJECT_VALUE_END;
            break;
        case JSON_OBJECT_VALUE_END:
            state = JSON_OBJECT_NEW;
            break;
        default:
            state = JSON_OBJECT_INDERERMINATE;
            break;
    }
    return state;
}
