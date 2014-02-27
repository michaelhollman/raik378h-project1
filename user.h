#ifndef _user_h
#define _user_h

#include <stdio.h>
#include <stdlib.h>

#define TEXT_SHORT      64
#define TEXT_LONG       1024


// user
typedef struct {
    int userId;
    int locationId;
    char name[TEXT_SHORT];
} user_t;


void print_user(user_t *user);

user_t *read_user(int fileNum);

void write_user(int fileNum, user_t *user);

void free_user(user_t *user);


#endif
