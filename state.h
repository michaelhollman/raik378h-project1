#ifndef _state_h
#define _state_h

#include <stdio.h>
#include <stdlib.h>

#define TEXT_SHORT      64
#define TEXT_LONG       1024


// state
typedef struct {
    int stateId;
    char name[TEXT_SHORT];
} state_t;


void print_state(state_t *state);

state_t *read_state(int fileNum);

void write_state(int fileNum, state_t *state);

void free_state(state_t *state);

int compare_states(const void *a, const void *b);

unsigned long hash_state(state_t *state);

#endif
