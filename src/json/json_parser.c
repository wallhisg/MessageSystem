#include <json/json_parser.h>

JsonConsume tok_letter_start(const char c, JsonConsume jsonConsume);
JsonConsume tok_l_curly(const char c, JsonConsume jsonConsume);
JsonConsume tok_r_curly(const char c, JsonConsume jsonConsume);
JsonConsume tok_l_bracket(const char c, JsonConsume jsonConsume);
JsonConsume tok_r_bracket(const char c, JsonConsume jsonConsume);
JsonConsume tok_colon(const char c, JsonConsume jsonConsume);
JsonConsume tok_comma(const char c, JsonConsume jsonConsume);
JsonConsume tok_dq_mark(const char c, JsonConsume jsonConsume);
JsonConsume tok_letter(const char c, JsonConsume jsonConsume);
void consume_all_char(Buffer *uartRxBuffer, int i);

int json_parser(JsonSchema *jsonSchema, BufferPtr uartRxBuffer)
{
    debug("BUFFER SIZE %d\r\n", uartRxBuffer->size);
    JsonSchema *schema = jsonSchema;

    JsonConsume jsonConsume;
    json_consume_init(&jsonConsume);
    jsonConsume.nextTok = tok_letter_start;

    char byte;
    int i = 0;
    for(i = 0; i < uartRxBuffer->size; i++)
    {
        byte = buffer_read_one_byte(uartRxBuffer);

        // block process string from uart buffer
        jsonConsume = consume_char(byte, jsonConsume);

        if(jsonConsume.tribool == TRIBOOL_TRUE)
        {
            schema->buff[schema->idx++] = byte;
        }
        else if(jsonConsume.tribool == TRIBOOL_FALSE)
        {
            debug_message("Json string false.\r\n");
            jsonConsume.type = JSON_TYPE_UNDEFINED;
            // read until get CR
            consume_all_char(uartRxBuffer, i);
        }
        // end block; end of json frame \n
        if(byte == LF)
            break;
    }

    if (jsonConsume.tribool == TRIBOOL_FALSE || jsonConsume.tribool == TRIBOOL_INDETERMINATE)
    {
        schema->type = JSON_TYPE_UNDEFINED;
    }
    else
    {
        schema->type = jsonConsume.type;
        schema->buff[schema->idx++] = LF;
    }

    return jsonConsume.tribool;
}

JsonConsume consume_char(char c, JsonConsume jsonConsume)
{

    JsonConsume consume;
    debug("tokCounter %u\r\n", jsonConsume.tokCounter);
    consume = jsonConsume.nextTok(c, jsonConsume);
    debug("consume_char: %d : >> \r\n", c);
    return consume;
}

JsonConsume tok_letter_start(const char c, JsonConsume jsonConsume)
{
    debug_message("tok_letter_start");

    JsonConsume consume = jsonConsume;

    switch (c)
    {
        case '\"': {
            consume.nextTok = tok_dq_mark;
            consume.tribool = TRIBOOL_INDETERMINATE;
            consume.type = JSON_TYPE_STRING;
            break;
        }
        case '{': {
            consume.nextTok = tok_l_curly;
            consume.tribool = TRIBOOL_INDETERMINATE;
            consume.type = JSON_TYPE_OBJECT;
            consume.tokCounter++;
            break;
        }
        default:
        {
            if ((c == LF) || (c == CR) || (c == '\0'))
            {
                consume.tribool = TRIBOOL_INDETERMINATE;
                consume.type = JSON_TYPE_UNDEFINED;
                consume.nextTok = tok_letter_start;
            }
            break;
        }
    }

    return consume;
}

// "
JsonConsume tok_dq_mark(const char c, JsonConsume jsonConsume)
{
    debug_message("tok_dq_mark");

    JsonConsume consume = jsonConsume;

    switch (c)
    {
        case ':': {
            consume.nextTok = tok_colon;
            consume.tribool = TRIBOOL_TRUE;
            break;
        }
        case ',': {
            consume.nextTok = tok_comma;
            consume.tribool = TRIBOOL_TRUE;
            break;
        }
        case '}': {
            consume.nextTok = tok_r_curly;
            consume.tokCounter--;

            if(consume.isObjects)
            {
                consume.tribool = TRIBOOL_TRUE;
                consume.isObjects = false;
            }
            else
                consume.tribool = TRIBOOL_INDETERMINATE;
            break;
        }
        case ']': {
            consume.nextTok = tok_r_bracket;
            consume.isObjects = false;
            consume.tribool = TRIBOOL_TRUE;
            consume.tokCounter--;
            break;
        }
        default: {
            if (isalpha(c) || isdigit(c))
            {
                consume.nextTok = tok_letter;
                consume.tribool = TRIBOOL_TRUE;
            }
            else if ((c == '\0') || (c == '\r') || (c == '\n'))
            {
                consume.tribool = TRIBOOL_TRUE;
            }
            else
            {
                consume.tribool = TRIBOOL_FALSE;
            }
            break;
        }
    }
    return consume;
}

// {
JsonConsume tok_l_curly(const char c, JsonConsume jsonConsume)
{
    debug_message("tok_l_curly");

    JsonConsume consume = jsonConsume;
    switch (c)
    {
        case  '\"': // {“
        {
            consume.nextTok = tok_dq_mark;
            consume.tribool = TRIBOOL_TRUE;
            break;
        }
        case ' ':   // space
        {
            consume.tribool = TRIBOOL_INDETERMINATE;
            break;
        }
        default:
            consume.tribool = TRIBOOL_FALSE;
            break;
    }

    return consume;
}

// }
JsonConsume tok_r_curly(const char c, JsonConsume jsonConsume)
{
    debug_message("tok_r_curly");

    JsonConsume consume = jsonConsume;

    switch (c)
    {
        case ',': {
            consume.nextTok = tok_comma;
            consume.tribool = TRIBOOL_TRUE;
            break;
        }
        case '\0':
        case '\r':
        case '\n':
        {
            consume.tribool = TRIBOOL_TRUE;
            break;
        }
        case '}': {
            consume.nextTok = tok_r_curly;
            consume.tokCounter--;

            if (consume.tokCounter > 1)
            {
                consume.tribool = TRIBOOL_TRUE;
            }
            else
            {
                consume.tribool = TRIBOOL_INDETERMINATE;
            }
            break;
        }
        default: {
            consume.tribool = TRIBOOL_FALSE;
            break;
        }
    }

    return consume;
}

//  [
JsonConsume tok_l_bracket(const char c, JsonConsume jsonConsume)
{
    debug_message("tok_l_bracket");

    JsonConsume consume = jsonConsume;
    // pending
    switch (c)
    {
        case '\"': {
            consume.nextTok = tok_dq_mark;
            consume.isObjects = true;
            consume.tribool = TRIBOOL_TRUE;
            break;
        }
        default:
            consume.tribool = TRIBOOL_FALSE;
            break;
    }

    return consume;
}

//  ]
JsonConsume tok_r_bracket(const char c, JsonConsume jsonConsume)
{
    debug_message("tok_r_bracket");

    JsonConsume consume = jsonConsume;

    switch (c)
    {
        case '}' : {
            consume.nextTok = tok_r_curly;
            consume.tribool = TRIBOOL_INDETERMINATE;
            consume.isObjects = false;
            break;
        }
        case ',' : {
            consume.nextTok = tok_comma;
            consume.tribool = TRIBOOL_TRUE;
            break;
        }
        case '\0':
        case '\r':
        case '\n':
        {
            consume.tribool = TRIBOOL_TRUE;
            break;
        }
        default:
            consume.tribool = TRIBOOL_FALSE;
            break;
    }

    return consume;
}

// :
JsonConsume tok_colon(const char c, JsonConsume jsonConsume)
{
    debug_message("tok_colon");

    JsonConsume consume = jsonConsume;
    switch (c)
    {
        case  '\"': {
            consume.nextTok = tok_dq_mark;
            consume.tribool = TRIBOOL_TRUE;
            break;
        }
        case '{': {
            consume.isObjects = true;
            consume.nextTok = tok_l_curly;
            consume.tribool = TRIBOOL_TRUE;
            consume.tokCounter++;
            break;
        }
        case '[': {
            consume.nextTok = tok_l_bracket;
            consume.tribool = TRIBOOL_TRUE;
            consume.type = JSON_TYPE_ARRAY;
            consume.isObjects = true;
            consume.tokCounter++;
            break;
        }
        default:
            consume.tribool = TRIBOOL_FALSE;
            break;
    }

    return consume;
}

//  ,
JsonConsume tok_comma(const char c, JsonConsume jsonConsume)
{
    debug_message("tok_comma");

    JsonConsume consume = jsonConsume;

    switch (c)
    {
        case  '\"': {
            consume.nextTok = tok_dq_mark;
            consume.tribool = TRIBOOL_TRUE;
            break;
        }
        default: {
            consume.tribool = TRIBOOL_FALSE;
            break;
        }
    }

    return consume;
}

//  0 -> 9; a -> Z
JsonConsume tok_letter(const char c, JsonConsume jsonConsume)
{
    debug_message("tok_letter");

    JsonConsume consume = jsonConsume;

    switch (c)
    {
        case '\"': {
            if (consume.type == JSON_TYPE_STRING)
            {
                consume.nextTok = tok_dq_mark;
                consume.tribool = TRIBOOL_INDETERMINATE;
            }
            else if (consume.type == JSON_TYPE_OBJECT)
            {
                consume.nextTok = tok_dq_mark;
                consume.tribool = TRIBOOL_TRUE;
            }
            else if (consume.type == JSON_TYPE_ARRAY)
            {
                consume.nextTok = tok_dq_mark;
                consume.tribool = TRIBOOL_TRUE;
            }
            break;
        }
        default: {
            if(isalpha(c) || isdigit(c))
            {
                consume.nextTok = tok_letter;
                consume.tribool = TRIBOOL_TRUE;
            }
            else
            {
                consume.tribool = TRIBOOL_FALSE;
            }
            break;
        }
    }

    return consume;
}

void consume_all_char(Buffer *uartRxBuffer, int i)
{
    char byte;
    int j = 0;
    for(j = i; j < uartRxBuffer->size; j++)
    {
        byte = buffer_read_one_byte(uartRxBuffer);
        if(byte == LF)
            break;
    }
}
