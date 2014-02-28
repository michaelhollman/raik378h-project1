#ifndef _make_tables_h
#define _make_tables_h

#include "user.h"
#include "message.h"
#include "timestamp.h"
#include "location.h"

//typedef struct user_node {
//    user_t user;
//    struct user_node *next;
//} user_node;

//typedef struct message_node {
//    message_t message;
//    struct message_node *next;
//} message_node;

typedef struct timestamp_node {
    timestamp_t timestamp;
    struct timestamp_node *next;
} timestamp_node;

typedef struct location_node {
    location_t location;
    struct location_node *next;
} location_node;


#endif
