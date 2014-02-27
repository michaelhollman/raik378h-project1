#include <stdio.h>
#include <stdlib.h>

#include "location.h"

// location
//    typedef struct {
//        int locationId;
//        char city[TEXT_SHORT];
//        char state[TEXT_SHORT];
//    } location_t;


void print_location(location_t *location)
{
    // location cannot be NULL
    if (location == NULL) {
        fprintf(stderr, "The location is NULL\n");
        exit(0);
    }
    
    // print location
    printf("Location: %08d\n", location->locationId);
    printf("\t%-12s: %s\n", "city", location->city);
    printf("\t%-12s: %s\n", "state", location->state);
}

location_t *read_location(int fileNum)
{
    // set up file
    FILE *fp;
    char filename[1024];
    sprintf(filename, "location_%08d.dat", fileNum);
    
    // open file
    fp = fopen(filename, "rb");
    
    if (!fp) {
        fprintf(stderr, "Cannot open %s\n", filename);
        exit(0);
    }
    
    // allocate memory for the record
    location_t *location = (location_t *)malloc(sizeof(location_t));
    
    // memory error
    if (location == NULL) {
        fprintf(stderr, "Cannot allocate memory for location.\n");
        exit(0);
    }
    
    // read location
    fread(&(location->locationId), sizeof(int), 1, fp);
    fread(&(location->city[0]), sizeof(char), TEXT_SHORT, fp);
    fread(&(location->state[0]), sizeof(char), TEXT_SHORT, fp);
    
    return location;
}

void write_location(int fileNum, location_t *location)
{
    // set up file
    FILE *fp;
    char filename[1024];
    sprintf(filename, "location_%08d.dat", fileNum);
    
    // open file
    fp = fopen(filename, "wb");
    if (!fp)
    {
        printf("Unable to open file.");
        return;
    }
    
    // write user
    fwrite(&(location->locationId), sizeof(int), 1, fp);
    fwrite(&(location->city[0]), sizeof(char), TEXT_SHORT, fp);
    fwrite(&(location->state[0]), sizeof(char), TEXT_SHORT, fp);
    
    fclose(fp);
}

void free_location(location_t *location)
{
    if (location == NULL) {
        return;
    }
    
    free(location);
}
