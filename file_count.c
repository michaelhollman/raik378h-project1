#include <stdio.h>
#include <stdlib.h>

#include "file_count.h"

//typedef struct {
//    int users;
//    int cities;
//    int states;
//    int messages;
//    int timestamps;
//    int datestamps;
//} file_count_t;


void print_file_count(file_count_t *fc)
{
    if (fc == NULL) {
        fprintf(stderr, "The file_count is NULL\n");
        exit(0);
    }
    
    printf("%-11s: %d\n","Users", fc->users);
    printf("%-11s: %d\n","Cities", fc->cities);
    printf("%-11s: %d\n","States", fc->states);
    printf("%-11s: %d\n","Messages", fc->messages);
    printf("%-11s: %d\n","Timestamps", fc->timestamps);
    printf("%-11s: %d\n","Datestamps", fc->datestamps);
    printf("%-11s: %d\n","Total", fc->users + fc->cities + fc->states + fc->messages + fc->timestamps + fc->datestamps);
}


file_count_t *read_file_count()
{
    // open file
    FILE *fp;
    fp = fopen("file_count.dat", "rb");
    if (!fp) {
        printf("Unable to open file_count. Make sure you run make_tables first!");
        exit(0);
    }
    
    // allocate memory for the record
    file_count_t *fc = (file_count_t *)malloc(sizeof(file_count_t));
    
    // memory error
    if (fc == NULL) {
        fprintf(stderr, "Cannot allocate memory for file_count.\n");
        exit(0);
    }
    
    // read file_count
    fread(&(fc->users), sizeof(int), 1, fp);
    fread(&(fc->cities), sizeof(int), 1, fp);
    fread(&(fc->states), sizeof(int), 1, fp);
    fread(&(fc->messages), sizeof(int), 1, fp);
    fread(&(fc->timestamps), sizeof(int), 1, fp);
    fread(&(fc->datestamps), sizeof(int), 1, fp);

    fclose(fp);

    return fc;
}

void write_file_count(file_count_t *fc)
{
    // open file
    FILE *fp;
    fp = fopen("file_count.dat", "wb");
    if (!fp) {
        printf("Unable to open file.");
        exit(0);
    }
    
    // memory error
    if (fc == NULL) {
        fprintf(stderr, "Cannot allocate memory for file_count.\n");
        exit(0);
    }
    
    // read file_count
    fwrite(&(fc->users), sizeof(int), 1, fp);
    fwrite(&(fc->cities), sizeof(int), 1, fp);
    fwrite(&(fc->states), sizeof(int), 1, fp);
    fwrite(&(fc->messages), sizeof(int), 1, fp);
    fwrite(&(fc->timestamps), sizeof(int), 1, fp);
    fwrite(&(fc->datestamps), sizeof(int), 1, fp);
    
    fclose(fp);

}

void free_file_count(file_count_t *fc)
{
    if (fc == NULL) {
        return;
    }
    
    free(fc);
}