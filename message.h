#ifndef _message_h
#define _message_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TEXT_SHORT      64
#define TEXT_LONG       1024


// message
typedef struct {
    int messageId;
    int userId;
    int timestampId;
    int datestampId;
    char text[TEXT_LONG];
} message_t;


void print_message(message_t *message);

message_t *read_message(int fileNum);

void write_message(int fileNum, message_t *message);

void free_message(message_t *message);


#endif
