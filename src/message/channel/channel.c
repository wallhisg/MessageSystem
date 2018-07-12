#include <message/channel/channel.h>

static Message GPIO_MESSAGES[MAX_NO_OF_GPIO_MESSAGE];
static Channel gpioChannel;

static Message UART_MESSAGES[MAX_NO_OF_UART_MESSAGE];
static Channel uartChannel;

static Message ADC_MESSAGES[MAX_NO_OF_ADC_MESSAGE];
static Channel adcChannel;

bool is_message_empty(Message message);

void channel_init()
{
    gpioChannel.messages = GPIO_MESSAGES;
    gpioChannel.size = MAX_NO_OF_GPIO_MESSAGE;

    uartChannel.messages = UART_MESSAGES;
    uartChannel.size = MAX_NO_OF_UART_MESSAGE;

    adcChannel.messages = ADC_MESSAGES;
    adcChannel.size = MAX_NO_OF_ADC_MESSAGE;
}

ChannelPtr get_channel(EndpointType epType)
{
    ChannelPtr channel = NULL;
    
    // Select channel
    switch (epType)
    {
        case ENDPOINT_GPIO:
        {
            channel = &gpioChannel;
            break;
        }
        case ENDPOINT_UART:
        {
            channel = &uartChannel;
            break;
        }
        case ENDPOINT_ADC:
        {
            channel = &adcChannel;
            break;
        }
        default:
            break;
    }
    
    return channel;
}



int find_free_message_slot(Message message[], size_t size)
{
    int messageSlot = 0;
    int slotFound = 0;

    size_t i = 0;
    for(i = 0; (i < size) && (slotFound == 0); ++i)
    {
        if(is_message_empty(message[i]))
        {
            messageSlot = i;
            messageSlot++;
        }
    }

    return messageSlot;
}

bool is_message_empty(Message message)
{
    return ((message.isUsed) ? false : true);
}
