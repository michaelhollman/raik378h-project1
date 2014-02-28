#ifndef _make_tables_h
#define _make_tables_h

#include "user.h"
#include "message.h"
#include "city.h"
#include "state.h"
#include "timestamp.h"
#include "datestamp.h"

typedef struct timestamp_node {
    timestamp_t timestamp;
    struct timestamp_node *next;
} timestamp_node;

typedef struct datestamp_node {
    datestamp_t datestamp;
    struct datestamp_node *next;
} datestamp_node;

typedef struct city_node {
    city_t city;
    struct city_node *next;
} city_node;

typedef struct state_node {
    state_t state;
    struct state_node *next;
} state_node;


//typedef struct user_node {
//    user_t user;
//    struct user_node *next;
//} user_node;

//typedef struct message_node {
//    message_t message;
//    struct message_node *next;
//} message_node;

#endif
