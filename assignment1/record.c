#include "record.h"

/**
 * print a message 
 */
void print_message(message_t *message)
{
    /* message cannot be NULL */
    if (message == NULL) {
        fprintf(stderr, "The message is NULL\n");
        exit(0);
    }

    /* print message time */
    printf("Time: %02d/%02d/%04d %02d:%02d\n", message->month, message->day, 
           message->year, message->hour, message->minute);
    
    /* print message text */
    printf("Text: %s\n", message->text);
}

/**
 * print a record 
 */
void print_record(record_t *record) 
{
    int i;
    
    /* record cannot be NULL */
    if (record == NULL) {
        fprintf(stderr, "The record is NULL\n");
        exit(0);
    }
    
    /* print user id */
    printf("ID: %06d\n", record->id);
    
    /* print user name */
    printf("Name: %s\n", record->name);
    
    /* print user location */
    printf("Location: %s\n", record->location);
    
    /* print message if the message number is greater than 0 */
    for (i = 0; i < record->message_num; i++) {
        print_message(&(record->messages[i]));
    }
}

/**
 * read a message from a file
 */
void read_message(message_t *message, FILE *fp)
{
    /* Assume file has been opened */
    if (fp == NULL) {
        fprintf(stderr, "The file stream is NULL\n");
        exit(0);
    }
    
    /* message cannot be NULL */
    if (message == NULL) {
        fprintf(stderr, "The message is NULL\n");
        exit(0);
    }
    
    /* read message text */
    fread(&(message->text[0]), sizeof(char), TEXT_LONG, fp);
    
    /* read message time */
    fread(&(message->year), sizeof(int), 1, fp);
    fread(&(message->month), sizeof(int), 1, fp);
    fread(&(message->day), sizeof(int), 1, fp);
    fread(&(message->hour), sizeof(int), 1, fp);
    fread(&(message->minute), sizeof(int), 1, fp);
}

/**
 * read a record from a file
 */
record_t *read_record(FILE *fp) 
{
    int i;      
    
    /* Assume file has been opened */
    if (fp == NULL) {
        fprintf(stderr, "The file stream is NULL\n");
        exit(0);
    }
    
    /* allocate memory for the record */
    record_t *record = (record_t *)malloc(sizeof(record_t));
    
    /* memory error */
    if (record == NULL) {
        fprintf(stderr, "Cannot allocate memory for record.\n");
        exit(0);
    }
    
    /* read user id */
    fread(&(record->id), sizeof(int), 1, fp);
    
    /* read user name */
    fread(&(record->name[0]), sizeof(char), TEXT_SHORT, fp);
    
    /* read user location */
    fread(&(record->location[0]), sizeof(char), TEXT_SHORT, fp);
    
    /* read message number */
    fread(&(record->message_num), sizeof(int), 1, fp);
    
    /* initalize messsages */
    record->messages = NULL;
    
    /* allocate memory for messages if the message number is greater than 0 */
    if (record->message_num > 0) {
        
        /*allocate memory */
        record->messages = (message_t *)malloc(sizeof(message_t) * 
                                               record->message_num);
        
        /* memory error */
        if (record->messages == NULL) {
            fprintf(stderr, "Cannot allocate memory for messages.\n");
            exit(0);    
        }
        
        /* read each message from file */
        for(i = 0; i < record->message_num; i++) {
            read_message(&(record->messages[i]), fp);
        }
    }
    
    /* return the record */
    return record;
}

/**
 * free memory of a record
 */
void free_record(record_t *record)
{
    if (record == NULL) {
        return;
    }
 
    /* free message memory */
    if (record->messages != NULL) {
        free(record->messages);
    }
    
    /* free record memory */
    free(record);
}

