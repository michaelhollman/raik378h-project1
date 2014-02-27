#include <stdio.h>
#include <stdlib.h>

// message
//    typedef struct {
//        int messageId;
//        int userId;
//        int timestampId;
//        char text[TEXT_SHORT];
//    } message_t;


void print_message(message_t *message){
    // message cannot be NULL
    if (message == NULL) {
        fprintf(stderr, "The message is NULL\n");
        exit(0);
    }

    // print message text
    printf("Text: %s\n", message->text);
}

message_t *read_message(FILE *fp)
{
    // Assume file has been opened
    if (fp == NULL) {
        fprintf(stderr, "The file stream is NULL\n");
        exit(0);
    }
    
    message_t *message = (message_t *)malloc(sizeof(message_t));
    
    // read message
    fread(&(message->messageId), sizeof(int), 1, fp);
    fread(&(message->userId), sizeof(int), 1, fp);
    fread(&(message->timestampId), sizeof(int), 1, fp);
    fread(&(message->text[0]), sizeof(char), TEXT_LONG, fp);
    
    return message;
}

void write_message(char *fileName, message_t *message);

void free_message(message_t *message)
{
    if (message == NULL) {
        return;
    }
    
    free(message);
}