#include <string.h>
#include <json/json_parser_object.h>

JsonConsume tok_obj_letter_start(const char c, JsonConsume objConsume);
JsonConsume tok_obj_dq_mark(const char c, JsonConsume objConsume);
JsonConsume tok_obj_colon(const char c, JsonConsume objConsume);
JsonConsume tok_obj_comma(const char c, JsonConsume objConsume);
JsonConsume tok_obj_letter(const char c, JsonConsume objConsume);
JsonConsume tok_obj_l_curly(const char c, JsonConsume objConsume);
JsonConsume tok_obj_r_curly(const char c, JsonConsume objConsume);
JsonConsume tok_obj_l_bracket(const char c, JsonConsume objConsume);
JsonConsume tok_obj_r_bracket(const char c, JsonConsume objConsume);


bool json_parser_object(Buffer *inBuff)
{
    bool result = false;

    JsonConsume objConsume;
    json_consume_init(&objConsume);
    objConsume.nextTok = tok_obj_letter_start;
    
    JsonValue keyValue;
    uint8_t keyIdx = 0;
    uint8_t valIdx = 0;

    char byte = ' ';

    while((inBuff->status != RING_STATUS_EMPTY) && (byte != LF))
    {
//         byte = read_one_byte_from_json_buffer();
        byte = buffer_read_one_byte(inBuff);
        objConsume = consume_object(byte, objConsume);

        if(objConsume.state == JSON_OBJECT_NEW)
        {
            memset(keyValue.key, 0, JSON_OBJECT_KEY_LENGTH * sizeof(char));
            memset(keyValue.value, 0, JSON_OBJECT_VALUE_LENGTH * sizeof(char));

            keyIdx = 0;
            valIdx = 0;

            objConsume.state = JSON_OBJECT_KEY;
        }
        else if(objConsume.state == JSON_OBJECT_END)
        {
            keyValue.key[keyIdx] = '\0';
            keyValue.value[valIdx] = '\0';
            if(!insert_json_object(keyValue))
            {
                // if false -> warning
                objConsume.tribool = TRIBOOL_FALSE;
                break;
            }

            objConsume.state = JSON_OBJECT_KEY;
        }

        if ((objConsume.tribool == TRIBOOL_TRUE) && (objConsume.state == JSON_OBJECT_KEY))
        {
            debug_json("KEY: byte: %c\r\n", byte);
            keyValue.key[keyIdx++] = byte;
        }
        else if ((objConsume.tribool == TRIBOOL_TRUE) && (objConsume.state = JSON_OBJECT_VALUE))
        {
            debug_json("VALUE: byte: %c\r\n", byte);
            keyValue.value[valIdx++] = byte;
        }
    }

    if(objConsume.tribool == TRIBOOL_TRUE)
        result = true;
    else {
        result = false;
    }

//    debug_json("result %lu\r\n", result);
    return result;
}

JsonConsume consume_object(const char c, JsonConsume objConsume)
{

    JsonConsume consume;
    consume = objConsume.nextTok(c, objConsume);
    debug_json("consume_char: %c : >> ", c);
    return consume;
}

JsonConsume tok_obj_letter_start(const char c, JsonConsume objConsume)
{

    printf("tok_obj_letter_start\r\n");
    debug_json("tok_obj_letter_start\r\n");
    JsonConsume consume = objConsume;

    switch (c) {
        case '\"' :
        {
            consume.nextTok = tok_obj_dq_mark;
            consume.tribool = TRIBOOL_INDETERMINATE;
            consume.state = JSON_OBJECT_NEW;
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
    debug_json("tok_obj_dq_mark");

    JsonConsume consume = objConsume;

    switch (c) {
        case ':' :
        {
            consume.nextTok = tok_obj_colon;
            consume.state = JSON_OBJECT_VALUE;
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
        case ',':
        {
            consume.nextTok = tok_obj_comma;
            if(consume.isObjects)
            {
                consume.tribool = TRIBOOL_TRUE;
            }
            else
            {
                consume.state = JSON_OBJECT_NEW;
                consume.tribool = TRIBOOL_INDETERMINATE;
            }
            break;
        }
        case '}':
        {
            consume.nextTok = tok_obj_r_curly;
            consume.state = JSON_OBJECT_END;
            consume.tribool = TRIBOOL_INDETERMINATE;
            consume.isObjects = false;
            break;
        }
        case ']' :
        {
            consume.nextTok = tok_obj_r_bracket;
            consume.state = JSON_OBJECT_END;
            consume.tribool = TRIBOOL_INDETERMINATE;
            consume.isObjects = false;
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
            if(isalpha(c) || isdigit(c))
            {
                consume.nextTok = tok_obj_letter;
                consume.tribool = TRIBOOL_TRUE;
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
    debug_json("tok_obj_colon");

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
                consume.state = JSON_OBJECT_VALUE;
            }
            break;
        }
        case '{':
        {
            consume.nextTok = tok_obj_l_curly;
            consume.isObjects = true;
            consume.tribool = TRIBOOL_INDETERMINATE;
            break;
        }
        case '[' :
        {
            consume.nextTok = tok_obj_l_bracket;
            consume.isObjects = true;
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
    debug_json("tok_obj_comma");

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
    debug_json("tok_obj_l_curly");

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
    debug_json("tok_obj_r_curly");

    JsonConsume consume = objConsume;

    switch (c) {
        case '\0':
        case '\r':
        case '\n':
        {
            consume.tribool = TRIBOOL_TRUE;
            consume.state = JSON_OBJECT_INDERERMINATE;
            break;
        }
        case ',' :
        {
            consume.nextTok = tok_obj_comma;
            consume.isObjects = false;
            consume.tribool = TRIBOOL_INDETERMINATE;
            consume.state = JSON_OBJECT_NEW;
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
    debug_json("tok_obj_letter");

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
                if(consume.state == JSON_OBJECT_VALUE)
                    consume.state = JSON_OBJECT_END;

                consume.tribool = TRIBOOL_INDETERMINATE;
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

JsonConsume tok_obj_l_bracket(const char c, JsonConsume objConsume)
{
    debug_json("tok_obj_l_bracket");

    JsonConsume consume = objConsume;

    switch (c) {
        case '\"' :
        {
            consume.nextTok = tok_obj_dq_mark;
            consume.tribool = TRIBOOL_TRUE;
            consume.state = JSON_OBJECT_VALUE;
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

JsonConsume tok_obj_r_bracket(const char c, JsonConsume objConsume)
{
    debug_json("tok_obj_r_bracket");

    JsonConsume consume = objConsume;

    switch (c) {
        case '\0':
        case '\r':
        case '\n':
        {
            consume.tribool = TRIBOOL_TRUE;
            consume.state = JSON_OBJECT_INDERERMINATE;
            break;
        }
        case ',' :
        {
            consume.nextTok = tok_obj_comma;
            consume.isObjects = false;
            consume.tribool = TRIBOOL_INDETERMINATE;
            consume.state = JSON_OBJECT_NEW;
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
