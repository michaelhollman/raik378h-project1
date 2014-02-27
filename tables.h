#ifndef __TABLES_H__
#define __TABLES_H__


#include <stdio.h>
#include <stdlib.h>

#define TEXT_SHORT      64
#define TEXT_LONG       1024


/* user structure */
typedef struct {
    int userId;                     /* user id */
    char name[TEXT_SHORT];      /* user name */
    int cityId;                 /* FK to city */
    int stateId;
} user_t;

/* city structure */
typedef struct {
    int cityId;
    char cityName[TEXT_SHORT];
    int stateId;
    char stateName[TEXT_SHORT];
} city_t;

typedef struct {
    int timestampId;
    int year;
    int month;
    int day;
    int hour;
    int minute;
} timestamp_t;

typedef struct {
    int messageId;
    int userId;
    int timestampId;
    char text[TEXT_SHORT];
} message_t;

void print_message(message_t *message);

void print_time(timestamp_t *time);

void read_message(message_t *message, FILE *fp);

extern user_t *read_user(FILE *fp);

timestamp_t *read_timestamp(FILE *fp);

city_t *read_city(FILE *fp);

#endif










