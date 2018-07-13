#include <message/message.h>
#include <message/router/router.h>

MessageHandle get_message_handle(void* message)
{
    const MessagePtr message_ = message;
    
    return message_->handle;
}


void handle_message()
{
    
}

void create_message()
{

}

void destroy_message()
{
    
}

