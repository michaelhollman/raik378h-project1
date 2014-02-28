#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "state.h"

// state
//    typedef struct {
//        int stateId;
//        char name[TEXT_SHORT];
//    } state_t;


void print_state(state_t *state)
{
    // state cannot be NULL
    if (state == NULL) {
        fprintf(stderr, "The state is NULL\n");
        exit(0);
    }
    
    // print state
    printf("state: %08d\n", state->stateId);
    printf("\t%-12s: %s\n", "name", state->name);
}

state_t *read_state(int fileNum)
{
    // set up file
    FILE *fp;
    char filename[1024];
    sprintf(filename, "state_%08d.dat", fileNum);
    
    // open file
    fp = fopen(filename, "rb");
    
    if (!fp) {
        fprintf(stderr, "Cannot open %s\n", filename);
        exit(0);
    }
    
    // allocate memory for the record
    state_t *state = (state_t *)malloc(sizeof(state_t));
    
    // memory error
    if (state == NULL) {
        fprintf(stderr, "Cannot allocate memory for state.\n");
        exit(0);
    }
    
    // read state
    fread(&(state->stateId), sizeof(int), 1, fp);
    fread(&(state->name[0]), sizeof(char), TEXT_SHORT, fp);
    
    fclose(fp);
    
    return state;
}

void write_state(int fileNum, state_t *state)
{
    // set up file
    FILE *fp;
    char filename[1024];
    sprintf(filename, "state_%08d.dat", fileNum);
    
    // open file
    fp = fopen(filename, "wb");
    if (!fp)
    {
        printf("Unable to open file.");
        return;
    }
    
    // write user
    fwrite(&(state->stateId), sizeof(int), 1, fp);
    fwrite(&(state->name[0]), sizeof(char), TEXT_SHORT, fp);
    
    fclose(fp);
}

void free_state(state_t *state)
{
    if (state == NULL) {
        return;
    }
    
    free(state);
}

int compare_states(const void *a, const void *b)
{
    return strcmp(((state_t *)a)->name, ((state_t *)b)->name);
}

unsigned long hash_state(state_t *state)
{
    char *str = state->name;
    unsigned long hash = 0, i;
    
    int len = strlen(str);
    len = (len > 5) ? 5 : len;
    
    for (i = 0; i < len; i++)
    {
        hash += ((int)str[i]) * pow(10, (len - i - 1) * 3);
    }
    return hash;
}
