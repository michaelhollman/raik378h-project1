#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>

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
    printf("Sorting tables starting...\n");
    
    // time the program
    struct timeval sysTimeStart, sysTimeEnd;
    gettimeofday(&sysTimeStart, NULL);
    
    int i;
    
    // get file counts
    file_count_t *fc = read_file_count();
    
    // note: wrapping each section in scopes { } so that the large arrays can be garbage collected once we're done with each one
    
    // users
    {
        printf("Sorting %d users\n", fc->users);
        
        // time this section
        struct timeval startSysTimeSub, endSysTimeSub;
        gettimeofday(&startSysTimeSub, NULL);
        
        // get count
        int count = fc->users;
        user_t users[count];
        
        // read
        for (i = 0; i < count; i++)
        {
            user_t *tmp = read_user(i);
            users[i] = *tmp;
            free_user(tmp);
        }
        
        // sort
        qsort(users, count, sizeof(users[0]), compare_users);
        
        // write
        for (i = 0; i < count; i++)
        {
            write_user(i, &users[i]);
            //print_user(&users[i]);
        }
        
        // end timing this section
        gettimeofday(&endSysTimeSub, NULL);
        float totalTime = (endSysTimeSub.tv_sec - startSysTimeSub.tv_sec)
        + (endSysTimeSub.tv_usec - startSysTimeSub.tv_usec) / 1000000.0f;
        printf("Table process time %f seconds\n", totalTime);
    }
    
    // states
    {
        printf("Sorting %d sates\n", fc->states);
        
        // time this section
        struct timeval startSysTimeSub, endSysTimeSub;
        gettimeofday(&startSysTimeSub, NULL);
        
        // get count
        int count = fc->states;
        state_t states[count];
        
        // read
        for (i = 0; i < count; i++)
        {
            state_t *tmp = read_state(i);
            states[i] = *tmp;
            free_state(tmp);
        }
        
        // sort
        qsort(states, count, sizeof(states[0]), compare_states);
        
        // write
        for (i = 0; i < count; i++)
        {
            write_state(i, &states[i]);
            //print_state(&states[i]);
        }
        
        // end timing this section
        gettimeofday(&endSysTimeSub, NULL);
        float totalTime = (endSysTimeSub.tv_sec - startSysTimeSub.tv_sec)
        + (endSysTimeSub.tv_usec - startSysTimeSub.tv_usec) / 1000000.0f;
        printf("Table process time %f seconds\n", totalTime);
    }
    
    // cities
    {
        printf("Sorting %d cities\n", fc->cities);
        
        // time this section
        struct timeval startSysTimeSub, endSysTimeSub;
        gettimeofday(&startSysTimeSub, NULL);
        
        // get count
        int count = fc->cities;
        city_t cities[count];
        
        // read
        for (i = 0; i < count; i++)
        {
            city_t *tmp = read_city(i);
            cities[i] = *tmp;
            free_city(tmp);
        }
        
        // sort
        qsort(cities, count, sizeof(cities[0]), compare_cities);
        
        // write
        for (i = 0; i < count; i++)
        {
            write_city(i, &cities[i]);
            //print_city(&cities[i]);
        }
        
        // end timing this section
        gettimeofday(&endSysTimeSub, NULL);
        float totalTime = (endSysTimeSub.tv_sec - startSysTimeSub.tv_sec)
        + (endSysTimeSub.tv_usec - startSysTimeSub.tv_usec) / 1000000.0f;
        printf("Table process time %f seconds\n", totalTime);
    }
    
    // messages
    // note: this sort uses the heap
    {
        printf("Sorting %d messages\n", fc->messages);
        
        
        // time this section
        struct timeval startSysTimeSub, endSysTimeSub;
        gettimeofday(&startSysTimeSub, NULL);
        
        // get count
        int count = fc->messages;
        message_t *messages = malloc(sizeof(message_t) * count);
        
        // read
        for (i = 0; i < count; i++)
        {
            message_t *tmp = read_message(i);
            messages[i] = *tmp;
            free_message(tmp);
        }
        
        // sort
        qsort(messages, count, sizeof(messages[0]), compare_messages);
        
        // write
        for (i = 0; i < count; i++)
        {
            write_message(i, &messages[i]);
            //print_city(&cities[i]);
        }
        
        free(messages);
        
        // end timing this section
        gettimeofday(&endSysTimeSub, NULL);
        float totalTime = (endSysTimeSub.tv_sec - startSysTimeSub.tv_sec)
        + (endSysTimeSub.tv_usec - startSysTimeSub.tv_usec) / 1000000.0f;
        printf("Table process time %f seconds\n", totalTime);
    }
    
    // timestamps
    {
        printf("Sorting %d timestamps\n", fc->timestamps);
        
        // time this section
        struct timeval startSysTimeSub, endSysTimeSub;
        gettimeofday(&startSysTimeSub, NULL);
        
        // get count
        int count = fc->timestamps;
        timestamp_t timestamps[count];
        
        // read
        for (i = 0; i < count; i++)
        {
            timestamp_t *tmp = read_timestamp(i);
            timestamps[i] = *tmp;
            free_timestamp(tmp);
        }
        
        // sort
        qsort(timestamps, count, sizeof(timestamps[0]), compare_timestamps);
        
        // write
        for (i = 0; i < count; i++)
        {
            write_timestamp(i, &timestamps[i]);
            //print_timestamp(&timestamps[i]);
        }
        
        // end timing this section
        gettimeofday(&endSysTimeSub, NULL);
        float totalTime = (endSysTimeSub.tv_sec - startSysTimeSub.tv_sec)
        + (endSysTimeSub.tv_usec - startSysTimeSub.tv_usec) / 1000000.0f;
        printf("Table process time %f seconds\n", totalTime);
    }
    
    // datestamps
    // sort (numeric)
    {
        printf("Sorting %d datestamps\n", fc->datestamps);
        
        // time this section
        struct timeval startSysTimeSub, endSysTimeSub;
        gettimeofday(&startSysTimeSub, NULL);
        
        // get count
        int count = fc->datestamps;
        datestamp_t datestamps[count];
        
        // read
        for (i = 0; i < count; i++)
        {
            datestamp_t *tmp = read_datestamp(i);
            datestamps[i] = *tmp;
            free_datestamp(tmp);
        }
        
        // sort
        qsort(datestamps, count, sizeof(datestamps[0]), compare_datestamps);
        
        // write
        for (i = 0; i < count; i++)
        {
            write_datestamp(i, &datestamps[i]);
            //print_datestamp(&datestamps[i]);
        }
        
        // end timing this section
        gettimeofday(&endSysTimeSub, NULL);
        float totalTime = (endSysTimeSub.tv_sec - startSysTimeSub.tv_sec)
        + (endSysTimeSub.tv_usec - startSysTimeSub.tv_usec) / 1000000.0f;
        printf("Table process time %f seconds\n", totalTime);
    }
    
    free_file_count(fc);
    
    // end timing the program
    gettimeofday(&sysTimeEnd, NULL);
    float totalTime = (sysTimeEnd.tv_sec - sysTimeStart.tv_sec)
    + (sysTimeEnd.tv_usec - sysTimeStart.tv_usec) / 1000000.0f;
    printf("Process time %f seconds\n", totalTime);
    
    return 0;
}