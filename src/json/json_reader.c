#include <json/json_reader.h>

extern JsonConsume tok_obj_letter_start(const char c, JsonConsume objConsume);
extern JsonConsume tok_obj_dq_mark(const char c, JsonConsume objConsume);
extern JsonConsume tok_obj_colon(const char c, JsonConsume objConsume);
extern JsonConsume tok_obj_comma(const char c, JsonConsume objConsume);
extern JsonConsume tok_obj_letter(const char c, JsonConsume objConsume);
extern JsonConsume tok_obj_l_curly(const char c, JsonConsume objConsume);
extern JsonConsume tok_obj_r_curly(const char c, JsonConsume objConsume);
extern JsonConsume tok_obj_l_bracket(const char c, JsonConsume objConsume);
extern JsonConsume tok_obj_r_bracket(const char c, JsonConsume objConsume);

char json_object_read_description(Buffer *inBuff)
{
    return json_read_description(inBuff, tok_obj_letter_start);
}

char json_read_description(Buffer* inBuff, void* tokStart)
{
    printf("json_obJect_read_description\r\n");
    JsonConsume objConsume;
    json_consume_init(&objConsume);
    objConsume.nextTok = tokStart;
    char description = 'a';
    char byte = ' ';
    byte = buffer_read_one_byte(inBuff);
    
    
    if(objConsume.state == JSON_OBJECT_NEW)
    {
        description = byte;
    }
    
    objConsume.nextTok(byte, objConsume);
    
//     if(objConsume.state == )
    
    printf("%c\r\n", description);
    return description;

}
