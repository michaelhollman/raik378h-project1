#include <stdio.h>
#include <stdlib.h>

#include "timestamp.h"

// timestamp
//    typedef struct {
//        int timestampId;
//        int year;
//        int month;
//        int day;
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
    printf("\tMM/DD/YYYY HH:MM: %02d/%02d/%04d %02d:%02d\n", timestamp->month, timestamp->day,
           timestamp->year, timestamp->hour, timestamp->minute);
}

timestamp_t *read_timestamp(int fileNum)
{
    // set up file
    FILE *fp;
    char filename[1024];
    sprintf(filename, "timestamp_%08d.dat", fileNum);
    
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
        fprintf(stderr, "Cannot allocate memory for city.\n");
        exit(0);
    }
    
    // read timestamp
    fread(&(timestamp->timestampId), sizeof(int), 1, fp);
    fread(&(timestamp->year), sizeof(int), 1, fp);
    fread(&(timestamp->month), sizeof(int), 1, fp);
    fread(&(timestamp->day), sizeof(int), 1, fp);
    fread(&(timestamp->hour), sizeof(int), 1, fp);
    fread(&(timestamp->minute), sizeof(int), 1, fp);
    
    return timestamp;
}

void write_timestamp(int fileNum, timestamp_t *timestamp)
{
    // set up file
    FILE *fp;
    char filename[1024];
    sprintf(filename, "timestamp_%08d.dat", fileNum);
    
    // open file
    fp = fopen(filename, "wb");
    if (!fp)
    {
        printf("Unable to open file.");
        return;
    }
    
    // write user
    fwrite(&(timestamp->timestampId), sizeof(int), 1, fp);
    fwrite(&(timestamp->year), sizeof(int), 1, fp);
    fwrite(&(timestamp->month), sizeof(int), 1, fp);
    fwrite(&(timestamp->day), sizeof(int), 1, fp);
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
