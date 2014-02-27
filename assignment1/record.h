#ifndef __RECORD_H__
#define __RECORD_H__

#include <stdio.h>
#include <stdlib.h>

#define TEXT_SHORT      64
#define TEXT_LONG       1024

/* message structure */
typedef struct {
    char text[TEXT_LONG];       /* text */
    int year;                   /* the send time of the message: */    
    int month;                  /* month/day/year hour:minute */
    int day;
    int hour;                   /* 0 - 23 */
    int minute;                 /* 0 - 59 */
} message_t;


/* record structure */
typedef struct {
    int id;                     /* user id */                                      
    char name[TEXT_SHORT];      /* user name */
    char location[TEXT_SHORT];  /* user location */
    int message_num;            /* number of send message */
    message_t *messages;        /* messages */
} record_t;


/**
 * print a record 
 */
void print_record(record_t *record);

/**
 * read a record from a file
 */
record_t *read_record(FILE *fp);

/**
 * free memory of a record
 */
void free_record(record_t *record);

#endif
