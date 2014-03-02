#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "message.h"

// message
//    typedef struct {
//        int messageId;
//        int userId;
//        int timestampId;
//        int datestampId;
//        char text[TEXT_SHORT];
//    } message_t;

void print_message(message_t *message)
{
    // message cannot be NULL
    if (message == NULL) {
        fprintf(stderr, "The message is NULL\n");
        exit(0);
    }

    printf("Message: %08d\n", message->messageId);
    printf("\t%-12s: %08d\n", "userId", message->userId);
    printf("\t%-12s: %08d\n", "timestampId", message->timestampId);
    printf("\t%-12s: %08d\n", "datestampId", message->datestampId);
    printf("\t%-12s: %s\n", "text", message->text);
}

message_t *read_message(int fileNum)
{
    // set up file
    FILE *fp;
    char filename[1024];
    sprintf(filename, "messages/message_%08d.dat", fileNum);
    
    // open file
    fp = fopen(filename, "rb");
    
    if (!fp) {
        fprintf(stderr, "Cannot open %s\n", filename);
        exit(0);
    }
    
    message_t *message = (message_t *)malloc(sizeof(message_t));
    
    // read message
    fread(&(message->messageId), sizeof(int), 1, fp);
    fread(&(message->userId), sizeof(int), 1, fp);
    fread(&(message->timestampId), sizeof(int), 1, fp);
    fread(&(message->datestampId), sizeof(int), 1, fp);
    fread(&(message->text[0]), sizeof(char), TEXT_LONG, fp);
    
    fclose(fp);

    return message;
}

void write_message(int fileNum, message_t *message)
{
    // set up file
    mkdir("messages", 0777);
    FILE *fp;
    char filename[1024];
    sprintf(filename, "messages/message_%08d.dat", fileNum);
    
    // open file
    fp = fopen(filename, "wb");
    if (!fp)
    {
        printf("Unable to open file.");
        return;
    }
    
    // write user
    fwrite(&(message->messageId), sizeof(int), 1, fp);
    fwrite(&(message->userId), sizeof(int), 1, fp);
    fwrite(&(message->timestampId), sizeof(int), 1, fp);
    fwrite(&(message->datestampId), sizeof(int), 1, fp);
    fwrite(&(message->text[0]), sizeof(char), TEXT_LONG, fp);
    
    fclose(fp);
}

void free_message(message_t *message)
{
    if (message == NULL) {
        return;
    }
    
    free(message);
}