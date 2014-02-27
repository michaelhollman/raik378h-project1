#include "tables.h"
#include "string.h"
#include "stdio.h"

#define TEXT_SHORT      64
#define TEXT_LONG       1024

int main()
//http://www.codingunit.com/c-tutorial-binary-file-io
{
    char *fileName;
    fileName = "userFile1.dat";
    testUserWrite(fileName);
    printf("Closed. Now reopening \n");
    testUserRead(fileName);


    return 0;


}

int testUserWrite(char *fileName) {
    FILE *ptr_userFile1;
    user_t user;
    ptr_userFile1=fopen(fileName, "wb");
    if (!ptr_userFile1)
    {
        printf("Unable to open file.");
        return 1;
    }

    user.userId = 2;
    strncpy(user.name, "Cassey", TEXT_SHORT);
    user.cityId = 1;
    user.stateId = 2;

    fwrite(&user, sizeof(user_t), 1, ptr_userFile1);
    fclose(ptr_userFile1);
    return 0;
}

int testUserRead(char *fileName) {

		FILE *ptr_file;
		user_t *user;

		ptr_file=fopen(fileName,"rb");
		if (!ptr_file)
		{
			printf("Unable to open file!");
			return 1;
		}
        user = read_user(ptr_file);
    
        /*
        fread(&readUser,sizeof(user_t),1,ptr_file);
        printf("%d\n",readUser.userId);
        printf("%s\n", readUser.name);
        */
    
        printf("%d\n", user->userId);
        printf("%s\n", user->name);
		fclose(ptr_file);
}
