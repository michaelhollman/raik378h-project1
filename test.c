#include <string.h>
#include <stdio.h>

#include "user.h"

int main()
{
    //http://www.codingunit.com/c-tutorial-binary-file-io
    //    char *fileName;
    //    fileName = "userFile1.dat";
    //    testUserWrite(fileName);
    //    printf("Closed. Now reopening \n");
    //    testUserRead(fileName);
    
    
    
    user_t user;
    
    user.userId = 1;
    user.locationId = 2;
    strncpy(user.name, "Cassey", TEXT_SHORT);
    
    print_user(&user);
    write_user(1,&user);

    user_t *read = read_user(1);
    
    print_user(read);
    
    return 0;
    
    
}