#include <message/message.h>
#include <message/router/router.h>

MessageHandle get_handle(void* message)
{
    const MessagePtr message_ = message;
    
    return message_->handle;
}

void handle_message()
{
    
}

void create_message(MessageHandle handle, handle_event_func handleEvent)
{
    printf("create_message\r\n");
    regist_message(handle, handleEvent);

}

void destroy_message()
{
    
}
