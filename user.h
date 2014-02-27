#ifndef _user_h
#define _user_h

#include <stdio.h>
#include <stdlib.h>

#define TEXT_SHORT      64
#define TEXT_LONG       1024


// user
typedef struct {
    int userId;
    char name[TEXT_SHORT];
    int cityId;
    int stateId;
} user_t;


void print_user(user_t *user);

user_t *read_user(FILE *fp);

void write_user(char *fileName, user_t *user);

void free_user(user_t *user);


#endif
