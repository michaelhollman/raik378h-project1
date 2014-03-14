#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "city.h"

// city
//    typedef struct {
//        int cityId;
//        int stateId
//        char name[TEXT_SHORT];
//    } city_t;

void print_city(city_t *city)
{
    // city cannot be NULL
    if (city == NULL) {
        fprintf(stderr, "The city is NULL\n");
        exit(0);
    }
    
    // print city
    printf("city: %08d\n", city->cityId);
    printf("\t%-12s: %08d\n", "stateId", city->stateId);
    printf("\t%-12s: %s\n", "name", city->name);
}

city_t *read_city(int fileNum)
{
    // set up file
    FILE *fp;
    char filename[1024];
    sprintf(filename, "cities/city_%08d.dat", fileNum);
    
    // open file
    fp = fopen(filename, "rb");
    
    if (!fp) {
        fprintf(stderr, "Cannot open %s\n", filename);
        exit(0);
    }
    
    // allocate memory for the record
    city_t *city = (city_t *)malloc(sizeof(city_t));
    
    // memory error
    if (city == NULL) {
        fprintf(stderr, "Cannot allocate memory for city.\n");
        exit(0);
    }
    
    // read city
    fread(&(city->cityId), sizeof(int), 1, fp);
    fread(&(city->stateId), sizeof(int), 1, fp);
    fread(&(city->name[0]), sizeof(char), TEXT_SHORT, fp);
    
    fclose(fp);
    
    return city;
}

void write_city(int fileNum, city_t *city)
{
    // set up file
    FILE *fp;
    char filename[1024];
    sprintf(filename, "cities/city_%08d.dat", fileNum);
    
    // open file
    fp = fopen(filename, "wb");
    if (!fp)
    {
        printf("Unable to open file.");
        return;
    }
    
    // write user
    fwrite(&(city->cityId), sizeof(int), 1, fp);
    fwrite(&(city->stateId), sizeof(int), 1, fp);
    fwrite(&(city->name[0]), sizeof(char), TEXT_SHORT, fp);
    
    fclose(fp);
}

void free_city(city_t *city)
{
    if (city == NULL) {
        return;
    }
    
    free(city);
}

int compare_cities(const void *a, const void *b)
{
    // sort by state id, then by city name
    int ids = (((city_t*)a)->stateId - ((city_t*)b)->stateId);
    if (ids != 0) return ids;
    return strcmp(((city_t*)a)->name , ((city_t*)b)->name);
}

unsigned long hash_city(city_t *city)
{
    char *str = city->name;
    unsigned long hash = 0, i;
    
    int len = strlen(str);
    len = (len > 5) ? 5 : len;
    
    // this is all pretty arbitrary
    for (i = 0; i < len; i++)
    {
        hash += ((int)str[i]) * pow(10, (len - i - 1) * 3);
    }
    return hash;
}
