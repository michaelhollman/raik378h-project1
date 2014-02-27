#include <stdio.h>
#include <stdlib.h>

#include "user.h"

// user
//    typedef struct {
//        int userId;
//        int locationId;
//        char name[TEXT_SHORT];
//    } user_t;


void print_user(user_t *user)
{
    // user cannot be NULL
    if (user == NULL) {
        fprintf(stderr, "The user is NULL\n");
        exit(0);
    }
    
    printf("User: %08d\n", user->userId);
    printf("\t%-12s: %s\n", "name", user->name);
    printf("\t%-12s: %08d\n", "locationId", user->locationId);
}

user_t *read_user(int fileNum)
{
    // set up file
    FILE *fp;
    char filename[1024];
    sprintf(filename, "user_%08d.dat", fileNum);
    
    // open file
    fp = fopen(filename, "rb");
    
    if (!fp) {
        fprintf(stderr, "Cannot open %s\n", filename);
        exit(0);
    }
    
    // allocate memory for the user
    user_t *user = (user_t *)malloc(sizeof(user_t));
    
    // memory error
    if (user == NULL) {
        fprintf(stderr, "Cannot allocate memory for user.\n");
        exit(0);
    }
    
    fread(&(user->userId), sizeof(int), 1, fp);
    fread(&(user->locationId), sizeof(int), 1, fp);
    fread(&(user->name[0]), sizeof(char), TEXT_SHORT, fp);
    
    return user;
}


void write_user(int fileNum, user_t *user)
{
    // set up file
    FILE *fp;
    char filename[1024];
    sprintf(filename, "user_%08d.dat", fileNum);
    
    // open file
    fp = fopen(filename, "wb");
    if (!fp)
    {
        printf("Unable to open file.");
        return;
    }

    // write user
    fwrite(&(user->userId), sizeof(int), 1, fp);
    fwrite(&(user->locationId), sizeof(int), 1, fp);
    fwrite(&(user->name[0]), sizeof(char), TEXT_SHORT, fp);
    
    fclose(fp);
}

void free_user(user_t *user)
{
    if (user == NULL) {
        return;
    }
    
    free(user);
}

int compare_users(user_t *a, user_t *b)
{
    // we're provided unique user ids in original data
    return (a->userId) - (b->userId);
}

unsigned long hash_user(user_t *user)
{
    return (unsigned long)user->userId;
}