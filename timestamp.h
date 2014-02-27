#ifndef _timestamp_h
#define _timestamp_h

#include <stdio.h>
#include <stdlib.h>

#define TEXT_SHORT      64
#define TEXT_LONG       1024


// timestamp
typedef struct {
    int timestampId;
    int year;
    int month;
    int day;
    int hour;
    int minute;
} timestamp_t;


void print_timestamp(timestamp_t *timestamp);

timestamp_t *read_timestamp(int fileNum);

void write_timestamp(int fileNum, timestamp_t *timestamp);

void free_timestamp(timestamp_t *timestamp);

int compare_timestamps(timestamp_t *a, timestamp_t *b);

unsigned long hash_timestamp(timestamp_t *timestamp);

#endif
