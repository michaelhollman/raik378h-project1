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
    
    int i;
    
    // get file counts
    file_count_t *fc = read_file_count();
    
    // note: wrapping each section in scopes { } so that the large arrays can be garbage collected once we're done with them
    
    
    // users
    // don't need to sort
    
    // states
    // sort (name alpha)
    {
        printf("%8d sates\n", fc->states);
        int count = fc->states;
        state_t states[count];
        
        // read
        for (i = 0; i < count; i++)
        {
            states[i] = *read_state(i);
        }
        
        // sort
        qsort(states, count, sizeof(states[0]), compare_states);
        
        // write
        for (i = 0; i < count; i++)
        {
            write_state(i, &states[i]);
            //print_state(&states[i]);
        }
    }
    
    // cities
    // sort (stateId numeric, name alpha)
    {
        printf("%8d cities\n", fc->cities);
        int count = fc->cities;
        city_t cities[count];
        
        // read
        for (i = 0; i < count; i++)
        {
            cities[i] = *read_city(i);
        }
        
        // sort
        qsort(cities, count, sizeof(cities[0]), compare_cities);
        
        // write
        for (i = 0; i < count; i++)
        {
            write_city(i, &cities[i]);
            //print_city(&cities[i]);
        }
    }
    
    // messages
    // don't need to sort
    
    // timestamps
    // sort (numeric)
    {
        printf("%8d timestamps\n", fc->timestamps);
        int count = fc->timestamps;
        timestamp_t timestamps[count];
        
        // read
        for (i = 0; i < count; i++)
        {
            timestamps[i] = *read_timestamp(i);
        }
        
        // sort
        // BROKEN
        // qsort(timestamps, count, sizeof(timestamps[0]), compare_timestamps);
        
        // write
        for (i = 0; i < count; i++)
        {
            write_timestamp(i, &timestamps[i]);
            print_timestamp(&timestamps[i]);
        }
    }
    
    // datestamps
    // sort (numeric)
    {
        
    }
    
    
    
    
    
    // generall idea:
    // load all files for some type into memory
    // qsort all objects
    // re-write all files
    
    // potentially optimize by renaming files instead of re-writing???
    
    
    
    free_file_count(fc);
    
    
    // end timing the program
    clock_t endTime = clock();
    double totaltime = (double)(endTime - startTime)/CLOCKS_PER_SEC;
    printf("\nProcess time %f seconds\n", totaltime);
}