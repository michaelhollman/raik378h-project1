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
    
    // location
    location_t location;
    location.locationId = 12345678;
    strncpy(location.city, "SomeCity", TEXT_SHORT);
    strncpy(location.state, "SomeState", TEXT_SHORT);
    
    print_location(&location);
    write_location(1,&location);
    location_t *readlocation = read_location(1);
    print_location(readlocation);
    
    // timestamp
    timestamp_t timestamp;
    timestamp.timestampId = 789423;
    timestamp.year = 2001;
    timestamp.month = 3;
    timestamp.day = 22;
    timestamp.hour = 14;
    timestamp.minute = 33;
    
    print_timestamp(&timestamp);
    write_timestamp(1, &timestamp);
    timestamp_t *readtimestamp = read_timestamp(1);
    print_timestamp(readtimestamp);
    
    return 0;
}