#ifndef _datestamp_h
#define _datestamp_h

#include <stdio.h>
#include <stdlib.h>

#define TEXT_SHORT      64
#define TEXT_LONG       1024


// datestamp
typedef struct {
    int datestampId;
    int year;
    int month;
    int day;
} datestamp_t;


void print_datestamp(datestamp_t *datestamp);

datestamp_t *read_datestamp(int fileNum);

void write_datestamp(int fileNum, datestamp_t *datestamp);

void free_datestamp(datestamp_t *datestamp);

int compare_datestamps(datestamp_t *a, datestamp_t *b);

unsigned long hash_datestamp(datestamp_t *datestamp);

#endif
