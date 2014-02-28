#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "make_tables.h"
#include "record.h"
#include "user.h"
#include "message.h"
#include "city.h"
#include "state.h"
#include "timestamp.h"
#include "datestamp.h"
#include "file_count.h"



int main(int argc, char **argv)
{
    // time the program
    clock_t startTime = clock();
    
    // TODO write a bunch of stuff
    
    // generall idea:
    // load all files for some type into memory
    // qsort all objects
    // re-write all files
    
    // potentially optimize by renaming files instead of re-writing???
    
    // end timing the program
    clock_t endTime = clock();
    double totaltime = (double)(endTime - startTime)/CLOCKS_PER_SEC;
    printf("\nProcess time %f seconds\n", totaltime);
}