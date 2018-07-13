#include <message/channel/channel.h>

static Message UART_MESSAGES[MAX_NO_OF_UART_MESSAGE];
static Channel uartChannel;

static Message SPI_MESSAGES[MAX_NO_OF_SPI_MESSAGE];
static Channel spiChannel;

static Message I2C_MESSAGES[MAX_NO_OF_I2C_MESSAGE];
static Channel i2cChannel;

bool is_message_empty(Message message);

void channel_init()
{
    uartChannel.messages = UART_MESSAGES;
    uartChannel.size = MAX_NO_OF_UART_MESSAGE;

    spiChannel.messages = SPI_MESSAGES;
    spiChannel.size = MAX_NO_OF_SPI_MESSAGE;

    i2cChannel.messages = I2C_MESSAGES;
    i2cChannel.size = MAX_NO_OF_I2C_MESSAGE;
}

ChannelPtr get_channel(EndpointType epType)
{
    ChannelPtr channel = NULL;
    
    // Select channel
    switch (epType)
    {
        case UART_ENDPOINT:
        {
            channel = &uartChannel;
            break;
        }
        case SPI_ENDPOINT:
        {
            channel = &spiChannel;
            break;
        }
        case I2C_ENDPOINT:
        {
            channel = &i2cChannel;
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
