#ifndef _city_h
#define _city_h

#include <stdio.h>
#include <stdlib.h>

#define TEXT_SHORT      64
#define TEXT_LONG       1024


// city
typedef struct {
    int cityId;
    int stateId;
    char name[TEXT_SHORT];
} city_t;


void print_city(city_t *city);

city_t *read_city(int fileNum);

void write_city(int fileNum, city_t *city);

void free_city(city_t *city);

int compare_cities(const void *a, const void *b);

unsigned long hash_city(city_t *city);

#endif
