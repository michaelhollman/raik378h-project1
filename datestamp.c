#include <stdio.h>
#include <stdlib.h>

#include "datestamp.h"

// datestamp
//    typedef struct {
//        int datestampId;
//        int year;
//        int month;
//        int day;
//    } datestamp_t;


void print_datestamp(datestamp_t *datestamp)
{
    // datestamp cannot be NULL
    if (datestamp == NULL) {
        fprintf(stderr, "The datestamp is NULL\n");
        exit(0);
    }
    
    printf("datestamp: %08d\n", datestamp->datestampId);
    printf("\tMM/DD/YYYY: %02d/%02d/%04d\n", datestamp->month, datestamp->day,
           datestamp->year);
}

datestamp_t *read_datestamp(int fileNum)
{
    // set up file
    FILE *fp;
    char filename[1024];
    sprintf(filename, "datestamp_%08d.dat", fileNum);
    
    // open file
    fp = fopen(filename, "rb");
    
    if (!fp) {
        fprintf(stderr, "Cannot open %s\n", filename);
        exit(0);
    }
    
    // allocate memory for the record
    datestamp_t *datestamp = (datestamp_t *)malloc(sizeof(datestamp_t));
    
    // memory error
    if (datestamp == NULL) {
        fprintf(stderr, "Cannot allocate memory for city.\n");
        exit(0);
    }
    
    // read datestamp
    fread(&(datestamp->datestampId), sizeof(int), 1, fp);
    fread(&(datestamp->year), sizeof(int), 1, fp);
    fread(&(datestamp->month), sizeof(int), 1, fp);
    fread(&(datestamp->day), sizeof(int), 1, fp);
    
    return datestamp;
}

void write_datestamp(int fileNum, datestamp_t *datestamp)
{
    // set up file
    FILE *fp;
    char filename[1024];
    sprintf(filename, "datestamp_%08d.dat", fileNum);
    
    // open file
    fp = fopen(filename, "wb");
    if (!fp)
    {
        printf("Unable to open file.");
        return;
    }
    
    // write user
    fwrite(&(datestamp->datestampId), sizeof(int), 1, fp);
    fwrite(&(datestamp->year), sizeof(int), 1, fp);
    fwrite(&(datestamp->month), sizeof(int), 1, fp);
    fwrite(&(datestamp->day), sizeof(int), 1, fp);
    
    fclose(fp);
}

void free_datestamp(datestamp_t *datestamp)
{
    if (datestamp == NULL) {
        return;
    }
    
    free(datestamp);
}

int compare_datestamps(datestamp_t *a, datestamp_t *b)
{
    return (hash_datestamp(a) - hash_datestamp(b));
}

unsigned long hash_datestamp(datestamp_t *datestamp){
    // YYYYMMDD
    return ((unsigned long)(datestamp->year)*1000) +
           ((unsigned long)(datestamp->month) * 100) +
           (unsigned long)(datestamp->day);
}
