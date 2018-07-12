#include <message/router/router.h>

bool add_to_registry(ChannelPtr channel, EndpointType type, void *instance);
bool remove_from_registry(ChannelPtr channel, EndpointType type, void *instance);

void regist_message(EndpointType type, void *message)
{
    ChannelPtr channel = get_channel(type);
    
    if(channel != NULL)
    {
        if(!add_to_registry(channel, type, message))
        {
            printf("No more registrations possible\r\n");
        }
    }
}

bool add_to_registry(ChannelPtr channel, EndpointType type, void *instance)
{
    MessagePtr message = channel->messages;
    bool isRegistered = false;
    
    size_t i = 0;
    for(i = 0; (i < channel->size) && isRegistered == false; ++i)
    {
        if(!message[i].isUsed)
        {
            MessagePtr freeEntry = &message[i];
            freeEntry->handle.endpoint = type;
            freeEntry->instance = instance;
        }
    }
    
    return isRegistered;
}

void unregist_message(EndpointType type, void *message)
{
    ChannelPtr channel = get_channel(type);
    
    if(channel != NULL)
    {
        if(!remove_from_registry(channel, type, message))
        {
            printf("Message not registered\r\n");
        }
    }
}

bool remove_from_registry(ChannelPtr channel, EndpointType type, void *instance)
{
    MessagePtr messages = channel->messages;
    bool nodeRemoved = false;
    
    size_t i = 0;
    for(i = 0; (i < channel->size) && (nodeRemoved == false); ++i)
    {
        if(messages[i].isUsed && (messages[i].instance = instance))
        {
            messages[i].isUsed = false;
            nodeRemoved = true;
        }
    }
    
    return nodeRemoved;
}
