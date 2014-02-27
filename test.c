#include <string.h>
#include <stdio.h>

#include "user.h"
#include "message.h"
#include "location.h"
#include "timestamp.h"

int main()
{
    // user
    user_t user;
    user.userId = 476;
    user.locationId = 3338;
    strncpy(user.name, "Cassey", TEXT_SHORT);
    
    print_user(&user);
    write_user(1,&user);
    user_t *readuser = read_user(1);
    print_user(readuser);
    
    // message
    message_t message;
    message.messageId = 987;
    message.userId = 654;
    message.timestampId = 321;
    strncpy(message.text, "Hello my name is Igor and I will be your friend.", TEXT_LONG);
    
    print_message(&message);
    write_message(1,&message);
    message_t *readmessage = read_message(1);
    print_message(readmessage);
    
    return 0;
}