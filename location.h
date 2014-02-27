#ifndef _location_h
#define _location_h

#include <stdio.h>
#include <stdlib.h>

#define TEXT_SHORT      64
#define TEXT_LONG       1024


// location
typedef struct {
    int locationId;
    char city[TEXT_SHORT];
    char state[TEXT_SHORT];
} location_t;


void print_location(location_t *location);

location_t *read_location(FILE *fp);

void write_location(char *fileName, location_t *location);

void free_location(location_t *location);


#endif
