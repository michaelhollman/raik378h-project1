#include <stdio.h>
#include <stdlib.h>
#include <record.h>

// location
//    typedef struct {
//        int locationId;
//        char city[TEXT_SHORT];
//        char state[TEXT_SHORT];
//    } location_t;


void print_location(location_t *location);

location_t *read_location(FILE *fp)
{
    // Assume file has been opened
    if (fp == NULL) {
        fprintf(stderr, "The file stream is NULL\n");
        exit(0);
    }
    
    // allocate memory for the record
    location_t *location = (location_t *)malloc(sizeof(location_t));
    
    // memory error
    if (location == NULL) {
        fprintf(stderr, "Cannot allocate memory for location.\n");
        exit(0);
    }
    
    fread(&(location->locationId), sizeof(int), 1, fp);
    fread(&(location->city[0]), sizeof(char), TEXT_SHORT, fp);
    fread(&(location->state[0]), sizeof(char), TEXT_SHORT, fp);
    
    return location;
}

void write_location(char *fileName, location_t *location);

void free_location(location_t *location)
{
    if (location == NULL) {
        return;
    }
    
    free(location);
}
