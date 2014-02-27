#ifndef _timestamp_h
#define _timestamp_h

#include <stdio.h>
#include <stdlib.h>

#define TEXT_SHORT      64
#define TEXT_LONG       1024


// timestamp
typedef struct {
    int timestampId;
    char name[TEXT_SHORT];
    int cityId;
    int stateId;
} timestamp_t;


void print_timestamp(timestamp_t *timestamp);

timestamp_t *read_timestamp(FILE *fp);

void write_timestamp(char *fileName, timestamp_t *timestamp);

void free_timestamp(timestamp_t *timestamp);


#endif
