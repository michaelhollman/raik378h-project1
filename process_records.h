#ifndef _process_records_h
#define _process_records_h

#include "user.h"
#include "message.h"
#include "timestamp.h"
#include "location.h"

typedef struct user_node_t {
    user_t user;
    struct user_note_t *next;
} user_node;

typedef struct message_node_t {
    message_t message;
    struct message_node_t *next;
} message_node;

typedef struct timestamp_node_t {
    timestamp_t timestamp;
    struct timestamp_node_t *next;
} timestamp_node;

typedef struct location_node_t {
    location_t location;
    struct location_node_t *next;
} location_node;

#endif
