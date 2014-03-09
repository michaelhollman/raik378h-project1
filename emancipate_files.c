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
    int i;
    unsigned long tot;
    
    remove("file_count.dat");
    
    // USERS
    i=0;
    sprintf(filename, "users/user_%08d.dat", i);
    while (remove(filename) == 0)
    {
        i++;
        sprintf(filename, "users/user_%08d.dat", i);
    }
    printf("Removed %d user files\n", i);
    tot += i;
    
    // CITIES
    i=0;
    sprintf(filename, "cities/city_%08d.dat", i);
    while (remove(filename) == 0)
    {
        i++;
        sprintf(filename, "cities/city_%08d.dat", i);
    }
    printf("Removed %d city files\n", i);
    tot += i;
    
    // STATES
    i=0;
    sprintf(filename, "states/state_%08d.dat", i);
    while (remove(filename) == 0)
    {
        i++;
        sprintf(filename, "states/state_%08d.dat", i);
    }
    printf("Removed %d state files\n", i);
    tot += i;
    
    // MESSAGES
    i=0;
    sprintf(filename, "messages/message_%08d.dat", i);
    while (remove(filename) == 0)
    {
        i++;
        sprintf(filename, "messages/message_%08d.dat", i);
    }
    printf("Removed %d message files\n", i);
    tot += i;
    
    // DATESTAMPS
    i=0;
    sprintf(filename, "datestamps/datestamp_%08d.dat", i);
    while (remove(filename) == 0)
    {
        i++;
        sprintf(filename, "datestamps/datestamp_%08d.dat", i);
    }
    printf("Removed %d datestamp files\n", i);
    tot += i;
    
    // TIMESTAMPS
    i=0;
    sprintf(filename, "timestamps/timestamp_%08d.dat", i);
    while (remove(filename) == 0)
    {
        i++;
        sprintf(filename, "timestamps/timestamp_%08d.dat", i);
    }
    printf("Removed %d timestamp files\n", i);
    tot += i;
    
    printf("Removed %lu files\n", tot);
    
    // end timing the program
    gettimeofday(&sysTimeEnd, NULL);
    float totalTime = (sysTimeEnd.tv_sec - sysTimeStart.tv_sec)
    + (sysTimeEnd.tv_usec - sysTimeStart.tv_usec) / 1000000.0f;
    printf("Process time %f seconds\n", totalTime);
    
    return 0;
}