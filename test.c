#include <string.h>
#include <stdio.h>
#include <string.h>

#include "user.h"
#include "message.h"
#include "city.h"
#include "state.h"
#include "timestamp.h"
#include "datestamp.h"

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
    
    if (compare_users(&user, readuser) == 0)
    {
        printf("%lu\n", hash_user(&user));
        printf("%lu\n", hash_user(readuser));
    }
    
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
    
//    // location
//    location_t location;
//    location.locationId = 12345678;
//    strncpy(location.city, "SomeCity", TEXT_SHORT);
//    strncpy(location.state, "SomeState", TEXT_SHORT);
//    
//    print_location(&location);
//    write_location(1,&location);
//    location_t *readlocation = read_location(1);
//    print_location(readlocation);
//    
//    if (compare_locations(&location, readlocation) == 0)
//    {
//        printf("%lu\n", hash_location(&location));
//        printf("%lu\n", hash_location(readlocation));
//    }
    
    // timestamp
    timestamp_t timestamp;
    timestamp.timestampId = 789423;
    timestamp.hour = 14;
    timestamp.minute = 33;
    
    print_timestamp(&timestamp);
    write_timestamp(1, &timestamp);
    timestamp_t *readtimestamp = read_timestamp(1);
    print_timestamp(readtimestamp);
    
    if (compare_timestamps(&timestamp, readtimestamp) == 0)
    {
        printf("%lu\n", hash_timestamp(&timestamp));
        printf("%lu\n", hash_timestamp(readtimestamp));
    }
    
    
    // location parsing
    char loc[TEXT_SHORT];
    strncpy(loc, NULL, TEXT_SHORT);
    
    char *city = strtok(loc, ",");
    char *state = strtok(NULL, ",");
    
    printf("city: %s\n", city);
    printf("state: %s\n", state);
    printf("%s\n", loc);
    
    
    return 0;
}