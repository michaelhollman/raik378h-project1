#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
    // time the program
    struct timeval sysTimeStart, sysTimeEnd;
    gettimeofday(&sysTimeStart, NULL);
    
    char filename[1024];
    int i, j;
    unsigned long tot;
    
    remove("file_count.dat");
    
    const char* const FILE_PREFIX[] = { "user", "state", "city", "message", "timestamp", "datestamp" };
    const char* const DIRECTORY_PREFIX[] = { "users", "states", "cities", "messages", "timestamps", "datestamps" };
    
    for (j = 0; j < 6; j++)
    {
        i=0;
        sprintf(filename, "%s/%s_%08d.dat", DIRECTORY_PREFIX[j] ,FILE_PREFIX[j], i);
        while (remove(filename) == 0)
        {
            i++;
            sprintf(filename, "%s/%s_%08d.dat", DIRECTORY_PREFIX[j] ,FILE_PREFIX[j], i);
        }
        printf("Removed %d %s files\n", i, FILE_PREFIX[j]);
        tot += i;
    }

    printf("Total: removed %lu files\n", tot);
    
    // end timing the program
    gettimeofday(&sysTimeEnd, NULL);
    float totalTime = (sysTimeEnd.tv_sec - sysTimeStart.tv_sec)
    + (sysTimeEnd.tv_usec - sysTimeStart.tv_usec) / 1000000.0f;
    printf("Process time %f seconds\n", totalTime);
    
    return 0;
}