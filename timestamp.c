#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "timestamp.h"

// timestamp
//    typedef struct {
//        int timestampId;
//        int hour;
//        int minute;
//    } timestamp_t;


void print_timestamp(timestamp_t *timestamp)
{
    // timestamp cannot be NULL
    if (timestamp == NULL) {
        fprintf(stderr, "The timestamp is NULL\n");
        exit(0);
    }
    
    printf("Timestamp: %08d\n", timestamp->timestampId);
    printf("\tHH:MM: %02d:%02d\n", timestamp->hour, timestamp->minute);
}

timestamp_t *read_timestamp(int fileNum)
{
    // set up file
    FILE *fp;
    char filename[1024];
    sprintf(filename, "timestamps/timestamp_%08d.dat", fileNum);
    
    // open file
    fp = fopen(filename, "rb");
    
    if (!fp) {
        fprintf(stderr, "Cannot open %s\n", filename);
        exit(0);
    }
    
    // allocate memory for the record
    timestamp_t *timestamp = (timestamp_t *)malloc(sizeof(timestamp_t));
    
    // memory error
    if (timestamp == NULL) {
        fprintf(stderr, "Cannot allocate memory for timestamp.\n");
        exit(0);
    }
    
    // read timestamp
    fread(&(timestamp->timestampId), sizeof(int), 1, fp);
    fread(&(timestamp->hour), sizeof(int), 1, fp);
    fread(&(timestamp->minute), sizeof(int), 1, fp);
    
    fclose(fp);
    
    return timestamp;
}

void write_timestamp(int fileNum, timestamp_t *timestamp)
{
    // set up file
    mkdir("timestamps", 0777);
    FILE *fp;
    char filename[1024];
    sprintf(filename, "timestamps/timestamp_%08d.dat", fileNum);
    
    // open file
    fp = fopen(filename, "wb");
    if (!fp)
    {
        printf("Unable to open file.");
        return;
    }
    
    // write user
    fwrite(&(timestamp->timestampId), sizeof(int), 1, fp);
    fwrite(&(timestamp->hour), sizeof(int), 1, fp);
    fwrite(&(timestamp->minute), sizeof(int), 1, fp);
    
    fclose(fp);
}

void free_timestamp(timestamp_t *timestamp)
{
    if (timestamp == NULL) {
        return;
    }
    
    free(timestamp);
}

int compare_timestamps(const void *a, const void *b)
{
    return ((int)hash_timestamp((timestamp_t *)a) - (int)hash_timestamp((timestamp_t *)b));
}

unsigned long hash_timestamp(timestamp_t *timestamp){
    // HHMM
    return (((unsigned long)timestamp->hour) * 100) +
           ((unsigned long)timestamp->minute);
}
