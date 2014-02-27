#include <stdio.h>
#include <stdlib.h>
#include <timestamp.h>

// timestamp
//    typedef struct {
//        int timestampId;
//        char name[TEXT_SHORT];
//        int cityId;
//        int stateId;
//    } timestamp_t;


void print_timestamp(timestamp_t *timestamp){
    printf("Time: %02d/%02d/%04d %02d:%02d\n", timestamp_t->month, timestamp_t->day,
           timestamp_t->year, timestamp_t->hour, timestamp_t->minute);
}

timestamp_t *read_timestamp(FILE *fp)
{
    // Assume file has been opened
    if (fp == NULL) {
        fprintf(stderr, "The file stream is NULL\n");
        exit(0);
    }
    
    // allocate memory for the record
    timestamp_t *timestamp = (timestamp_t *)malloc(sizeof(timestamp_t));
    
    // memory error
    if (timestamp == NULL) {
        fprintf(stderr, "Cannot allocate memory for city.\n");
        exit(0);
    }
    
    fread(&(timestamp->timestampId), sizeof(int), 1, fp);
    fread(&(timestamp->year), sizeof(int), 1, fp);
    fread(&(timestamp->month), sizeof(int), 1, fp);
    fread(&(timestamp->day), sizeof(int), 1, fp);
    fread(&(timestamp->hour), sizeof(int), 1, fp);
    fread(&(timestamp->minute), sizeof(int), 1, fp);
    
    return timestamp;
}

void write_timestamp(char *fileName, timestamp_t *timestamp);

void free_timestamp(timestamp_t *timestamp)
{
    if (timestamp == NULL) {
        return;
    }
    
    free(timestamp);
}
