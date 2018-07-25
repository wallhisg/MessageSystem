#include <driver/ring_buffer.h>
#include <system_init.h>
#include <json/json.h>
#include <json/json_parser.h>

extern Buffer rxBuf;

#define MAX_NO_OF_BUFFER    20
static char buffer[MAX_NO_OF_BUFFER];
volatile uint16_t bytesWritten = 0;

void TEST_JSON_STRING()
{
    printf("--- TEST_JSON_STRING ---\r\n");
    memset(buffer, 0, MAX_NO_OF_BUFFER);
    
    // init value to write
    char *bytesWrite = "\"abcdef123\"\r\n";
    uint8_t bytesWritten = strlen(bytesWrite);

    memcpy(buffer, bytesWrite, bytesWritten);
    printf("json string input in HEX: \r\n");
    int i = 0;
    for(i = 0; i < bytesWritten; i++)
    {
        printf(" %x", bytesWrite[i]);
    }    
    
    printf("\r\n");
    printf("json string input in CHAR: %s\r\n", bytesWrite);

    char byte = 0;    
    for(i = 0; i < bytesWritten; i++)
    {
        byte = buffer[i];
        buffer_write_one_byte(&rxBuf, byte);
    }    
    
    printf("json string output: \r\n");
    // parser json string
    JsonSchema *jsonSchema = get_json_schema();
    if(json_parser(jsonSchema, &rxBuf))
    {
        if(jsonSchema->type == JSON_TYPE_STRING)
        {
            // print out json_parser result
            printf("jsonSchema type: %d\r\n", jsonSchema->type);
            printf("jsonSchema idx: %d\r\n", jsonSchema->idx);
            printf("jsonSchema buff in HEX: \r\n");

            int j = jsonSchema->idx;
            for(i = 0; i < j; i++)
            {
                printf(" %x", jsonSchema->buff[i]);
            }
            jsonSchema->buff[jsonSchema->idx] = '\0';
            printf("\r\n");
            printf("string out: %s\r\n", jsonSchema->buff);
        }
    }    
}

int main()
{
    system_init();
    json_init();
    
    TEST_JSON_STRING();
    
    
    return 0;
}
