#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    
    char filename[1024];
    int i;
    unsigned long tot;
    
    // USERS
    i=0;
    sprintf(filename, "user_%08d.dat", i);
    while (remove(filename) == 0)
    {
        i++;
        sprintf(filename, "user_%08d.dat", i);
    }
    printf("Removed %d user files\n", i);
    tot += i;
    
    // CITIES
    i=0;
    sprintf(filename, "city_%08d.dat", i);
    while (remove(filename) == 0)
    {
        i++;
        sprintf(filename, "city_%08d.dat", i);
    }
    printf("Removed %d city files\n", i);
    tot += i;
    
    // STATES
    i=0;
    sprintf(filename, "state_%08d.dat", i);
    while (remove(filename) == 0)
    {
        i++;
        sprintf(filename, "state_%08d.dat", i);
    }
    printf("Removed %d state files\n", i);
    tot += i;

    // DATESTAMPS
    i=0;
    sprintf(filename, "datestamp_%08d.dat", i);
    while (remove(filename) == 0)
    {
        i++;
        sprintf(filename, "datestamp_%08d.dat", i);
    }
    printf("Removed %d datestamp files\n", i);
    tot += i;

    // TIMESTAMPS
    i=0;
    sprintf(filename, "timestamp_%08d.dat", i);
    while (remove(filename) == 0)
    {
        i++;
        sprintf(filename, "timestamp_%08d.dat", i);
    }
    printf("Removed %d timestamp files\n", i);
    tot += i;

    // MESSAGES
    i=0;
    sprintf(filename, "message_%08d.dat", i);
    while (remove(filename) == 0)
    {
        i++;
        sprintf(filename, "message_%08d.dat", i);
    }
    printf("Removed %d message files\n", i);
    tot += i;
    
    printf("Removed %lu files\n", tot);
    
    return 0;
}