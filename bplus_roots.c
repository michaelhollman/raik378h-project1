#include <stdio.h>
#include <stdlib.h>

#include "bplus_roots.h"

//typedef struct {
//    int user;
//    int city;
//    int state;
//    int message;
//    int timestamp;
//    int datestamp;
//} bplus_roots_t;

void print_bplus_roots(bplus_roots_t *bpr)
{
    if (bpr == NULL) {
        fprintf(stderr, "The file_count is NULL\n");
        exit(0);
    }
    
    printf("B+ tree roots\n");
    printf("%-11s: %d\n","User", bpr->user);
    printf("%-11s: %d\n","City", bpr->city);
    printf("%-11s: %d\n","State", bpr->state);
    printf("%-11s: %d\n","Message", bpr->message);
    printf("%-11s: %d\n","Timestamp", bpr->timestamp);
    printf("%-11s: %d\n","Datestamp", bpr->datestamp);
}

bplus_roots_t *read_bplus_roots()
{
    // open file
    FILE *fp;
    fp = fopen("bplus_roots.dat", "rb");
    if (!fp) {
        printf("Unable to open bplus_roots.dat. Make sure you run make_tables and make_bplus_trees first!\n");
        exit(0);
    }
    
    // allocate memory for the record
    bplus_roots_t *bpr = (bplus_roots_t *)malloc(sizeof(bplus_roots_t));
    
    // memory error
    if (bpr == NULL) {
        fprintf(stderr, "Cannot allocate memory for bplus_roots.\n");
        exit(0);
    }
    
    // read file_count
    fread(&(bpr->user), sizeof(int), 1, fp);
    fread(&(bpr->city), sizeof(int), 1, fp);
    fread(&(bpr->state), sizeof(int), 1, fp);
    fread(&(bpr->message), sizeof(int), 1, fp);
    fread(&(bpr->timestamp), sizeof(int), 1, fp);
    fread(&(bpr->datestamp), sizeof(int), 1, fp);

    fclose(fp);

    return bpr;
}

void write_bplus_roots(bplus_roots_t *bpr)
{
    // open file
    FILE *fp;
    fp = fopen("bplus_roots.dat", "wb");
    if (!fp) {
        printf("Unable to open bplus_roots.dat for writing.\n");
        exit(0);
    }
    
    // read file_count
    fwrite(&(bpr->user), sizeof(int), 1, fp);
    fwrite(&(bpr->city), sizeof(int), 1, fp);
    fwrite(&(bpr->state), sizeof(int), 1, fp);
    fwrite(&(bpr->message), sizeof(int), 1, fp);
    fwrite(&(bpr->timestamp), sizeof(int), 1, fp);
    fwrite(&(bpr->datestamp), sizeof(int), 1, fp);
    
    fclose(fp);
}

void free_bplus_roots(bplus_roots_t *bpr)
{
    if (bpr == NULL) {
        return;
    }
    
    free(bpr);
}