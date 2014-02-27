#include <stdio.h>
#include <stdlib.h>
#include <user.h>

// user
//    typedef struct {
//        int userId;
//        char name[TEXT_SHORT];
//        int cityId;
//        int stateId;
//    } user_t;


void print_user(user_t *user);

user_t *read_user(FILE *fp)
{
    // Assume file has been opened
    if (fp == NULL) {
        fprintf(stderr, "The file stream is NULL\n");
        exit(0);
    }
    
    // allocate memory for the user
    user_t *user = (user_t *)malloc(sizeof(user_t));
    
    // memory error
    if (user == NULL) {
        fprintf(stderr, "Cannot allocate memory for user.\n");
        exit(0);
    }
    
    // read user id
    fread(&(user->userId), sizeof(int), 1, fp);
    
    // read user name
    fread(&(record->name[0]), sizeof(char), TEXT_SHORT, fp);
    
    // read cityId
    fread(&(record->cityId), sizeof(int), 1, fp);
    
    // read stateId
    fread(&(record->stateId), sizeof(int), 1, fp);
    
    // return the user
    return user;
}


void write_user(char *fileName, user_t *user);

void free_user(user_t *user)
{
    if (user == NULL) {
        return;
    }
    
    free(user);
}
