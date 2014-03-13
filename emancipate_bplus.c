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
    
    remove("bplus_roots.dat");
    
    const char* const FILE_PREFIX[] = { "user", "state", "city", "message", "timestamp", "datestamp" };

    for (j = 0; j < 6; j++)
    {
        i=0;
        sprintf(filename, "bplus/%s_node_%08d.dat", FILE_PREFIX[j], i);
        while (remove(filename) == 0)
        {
            i++;
            sprintf(filename, "bplus/%s_node_%08d.dat", FILE_PREFIX[j], i);
        }
        printf("Removed %d %s b+ nodes\n", i, FILE_PREFIX[j]);
        tot += i;
    }
    
    printf("Total: removed %lu b+ nodes\n", tot);
    
    // end timing the program
    gettimeofday(&sysTimeEnd, NULL);
    float totalTime = (sysTimeEnd.tv_sec - sysTimeStart.tv_sec)
    + (sysTimeEnd.tv_usec - sysTimeStart.tv_usec) / 1000000.0f;
    printf("Process time %f seconds\n", totalTime);
    
    return 0;
}