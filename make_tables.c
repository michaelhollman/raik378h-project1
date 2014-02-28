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

// arbitrary large prime number
#define HASH_SIZE 1009

int main(int argc, char **argv)
{
    //print usage if needed
    if (argc != 2) {
        fprintf(stderr, "Usage: %s totalRecordNumber\n", argv[0]);
        exit(0);
    }
    //get total record number from argument
    int totalRecordNumber = atoi(argv[1]);
    
    // time the program
    clock_t startTime = clock();
    
    // set up some counters, etc.
    unsigned int recordCount = 0,
    userCount = 0,
    cityCount = 0,
    stateCount = 0,
    timestampCount = 0,
    datestampCount = 0,
    messageCount = 0,
    i,j,k;
    
    
    // SET UP HASH TABLES FOR CITIES, STATES, TIMESTAMPS, DATESTAMPS
    // cities
    city_node *cityHT[HASH_SIZE];
    for (i = 0; i < HASH_SIZE; i++)
    {
        cityHT[i] = malloc(sizeof(city_node));
        cityHT[i] = NULL;
    }
    
    // states
    state_node *stateHT[HASH_SIZE];
    for (i = 0; i < HASH_SIZE; i++)
    {
        stateHT[i] = malloc(sizeof(state_node));
        stateHT[i] = NULL;
    }
    
    // timestamps
    timestamp_node *timestampHT[HASH_SIZE];
    for (i = 0; i < HASH_SIZE; i++)
    {
        timestampHT[i] = malloc(sizeof(timestamp_node));
        timestampHT[i] = NULL;
    }
    
    // datestamps
    datestamp_node *datestampHT[HASH_SIZE];
    for (i = 0; i < HASH_SIZE; i++)
    {
        datestampHT[i] = malloc(sizeof(datestamp_node));
        datestampHT[i] = NULL;
    }
    
    // LOOP OVER RECORD FILES
    char filename[1024];
    FILE *fp = NULL;
    for (i = 0; i < totalRecordNumber; i++) {
        //open the corresponding file
        sprintf(filename, "record_%06d.dat", i);
        fp = fopen(filename,"rb");
        if (!fp) {
            fprintf(stderr, "Cannot open %s\n", filename);
            exit(0);
        }
        
        // read the record from the file
        record_t *record = read_record(fp);
        
        // split location into city and state, as best we can
        char cityStr[TEXT_SHORT];
        char stateStr[TEXT_SHORT];
        
        // there's a few records where the location is \0, which strtok breaks on
        if (record->location[0] == '\0')
        {
            strncpy(cityStr, "", TEXT_SHORT);
            strncpy(stateStr, "", TEXT_SHORT);
        }
        else
        {
            char loc[TEXT_SHORT];
            strncpy(loc, record->location, TEXT_SHORT);
            strncpy(cityStr, strtok(loc, ","), TEXT_SHORT);
            strncpy(stateStr, strtok(NULL, ","), TEXT_SHORT);
        }
        
        // create state
        state_t state;
        strncpy(state.name, stateStr, TEXT_SHORT);
        
        // get stateId from hash if we have it already
        unsigned int stateHash = hash_state(&state) % HASH_SIZE;
        state_node *s;
        int stateId = -1;
        for(s = stateHT[stateHash]; (s != NULL) && (stateId == -1); s = s->next)
        {
            if (compare_states(&state, &(s->state)) == 0)
            {
                //printf("State already found: %20s: %d\n", s->state.name, s->state.stateId);
                stateId = s->state.stateId;
            }
        }
        
        // assign stateId, add to hash table, and write file if we don't have it
        if (stateId == -1)
        {
            state.stateId = stateCount;
            stateId = stateCount;
            write_state(stateCount, &state);
            stateCount++;
            
            s = malloc(sizeof(state_node));
            s->state = state;
            s->next = stateHT[stateHash];
            stateHT[stateHash] = s;
        }
        
        // create city
        city_t city;
        city.stateId = stateId;
        strncpy(city.name, cityStr, TEXT_SHORT);
        
        // get cityId from hash if we have it already
        unsigned int cityHash = hash_city(&city) % HASH_SIZE;
        city_node *c;
        int cityId = -1;
        for(c = cityHT[cityHash]; (c != NULL) && (cityId == -1); c = c->next)
        {
            if (compare_cities(&city, &(c->city)) == 0)
            {
                //printf("City already found: %20s (%d): %d\n", c->city.name, c->city.stateId, c->city.cityId);
                cityId = c->city.cityId;
            }
        }
        
        // assign cityId, add to hash table, and write file if we don't have it
        if (cityId == -1)
        {
            city.cityId = cityCount;
            cityId = cityCount;
            write_city(cityCount, &city);
            cityCount++;
            
            c = malloc(sizeof(city_node));
            c->city = city;
            c->next = cityHT[cityHash];
            cityHT[cityHash] = c;
        }
        
        
        // create and write user
        user_t user;
        user.userId = record->id;
        user.cityId = cityId;
        strncpy(user.name, record->name, TEXT_SHORT);
        write_user(userCount, &user);
        userCount++;
        
        // loop over messages
        for(j = 0; j < record->message_num; j++) {
            // create timestamp
            timestamp_t timestamp;
            timestamp.hour = record->messages[j].hour;
            timestamp.minute = record->messages[j].minute;
            
            // get timestampId from hash if we have it already
            unsigned int timestampHash = hash_timestamp(&timestamp) % HASH_SIZE;
            timestamp_node *t;
            int tsId = -1;
            for(t = timestampHT[timestampHash]; (t != NULL) && (tsId == -1); t = t->next)
            {
                if (compare_timestamps(&timestamp, &(t->timestamp)) == 0)
                {
                    //printf("Timestamp already found: %02d:%02d: %d\n", t->timestamp.hour, t->timestamp.minute, t->timestamp.timestampId);
                    tsId = t->timestamp.timestampId;
                }
            }
            
            // assign timestampId, add to hash table, and write file if we don't have it
            if (tsId == -1)
            {
                timestamp.timestampId = timestampCount;
                tsId = timestampCount;
                write_timestamp(timestampCount, &timestamp);
                timestampCount++;
                
                t = malloc(sizeof(timestamp_node));
                t->timestamp = timestamp;
                t->next = timestampHT[timestampHash];
                timestampHT[timestampHash] = t;
            }
            
            // create datestamp
            datestamp_t datestamp;
            datestamp.year = record->messages[j].year;
            datestamp.month = record->messages[j].month;
            datestamp.day = record->messages[j].day;
            
            // get datestampId from hash if we have it already
            unsigned int datestampHash = hash_datestamp(&datestamp) % HASH_SIZE;
            datestamp_node *d;
            int dsId = -1;
            for(d = datestampHT[datestampHash]; (d != NULL) && (dsId == -1); d = d->next)
            {
                if (compare_datestamps(&datestamp, &(d->datestamp)) == 0)
                {
                    //printf("Datestamp already found: %02d/%02d/%04d: %d\n", d->datestamp.month, d->datestamp.day, d->datestamp.year, d->datestamp.datestampId );
                    dsId = d->datestamp.datestampId;
                }
            }
            
            // assign datestampId, add to hash table, and write file if we don't have it
            if (dsId == -1)
            {
                datestamp.datestampId = datestampCount;
                tsId = datestampCount;
                write_datestamp(datestampCount, &datestamp);
                datestampCount++;
                
                d = malloc(sizeof(datestamp_node));
                d->datestamp = datestamp;
                d->next = datestampHT[datestampHash];
                datestampHT[datestampHash] = d;
            }
            
            message_t message;
            strncpy(message.text, record->messages[j].text, TEXT_LONG);
            message.userId = user.userId;
            message.timestampId = tsId;
            message.datestampId = dsId;
            message.messageId = messageCount;
            
            write_message(messageCount, &message);
            messageCount++;
        }
        
        // free record
        free_record(record);
        // close the file
        fclose(fp);
        
        if ((i + 1) % 1000 == 0){
            printf("%d\n",i);
            printf("\t%-11s: %d\n","Users",userCount);
            printf("\t%-11s: %d\n","Cities",cityCount);
            printf("\t%-11s: %d\n","States",stateCount);
            printf("\t%-11s: %d\n","Messages",messageCount);
            printf("\t%-11s: %d\n","Timestamps",timestampCount);
            printf("\t%-11s: %d\n","Datestamps",datestampCount);
            printf("\t%-11s: %d\n","Total",userCount + cityCount + stateCount + messageCount + timestampCount + datestampCount);
            printf("\n");
        }
    }
    // done processing all files
    
    // free city nodes
    city_node *cNode;
    for (i = 0; i < HASH_SIZE; i++)
    {
    	cNode = cityHT[i];
    	while (cNode != NULL)
    	{
    		city_node* tmp = cNode;
    		cNode = cNode->next;
    		free (tmp);
    	}
    }
    
    // free state nodes
    state_node *sNode;
    for (i = 0; i < HASH_SIZE; i++)
    {
    	sNode = stateHT[i];
    	while (sNode != NULL)
    	{
    		state_node* tmp = sNode;
    		sNode = sNode->next;
    		free (tmp);
    	}
    }
    
    // free timestamp nodes
    timestamp_node *tNode;
    for (i = 0; i < HASH_SIZE; i++)
    {
    	tNode = timestampHT[i];
    	while (tNode != NULL)
    	{
    		timestamp_node* tmp = tNode;
    		tNode = tNode->next;
    		free (tmp);
    	}
    }
    
    // free datestamp nodes
    datestamp_node *dNode;
    for (i = 0; i < HASH_SIZE; i++)
    {
    	dNode = datestampHT[i];
    	while (dNode != NULL)
    	{
    		datestamp_node* tmp = dNode;
    		dNode = dNode->next;
    		free (tmp);
    	}
    }
    
    file_count_t fc;
    fc.users = userCount;
    fc.cities = cityCount;
    fc.states = stateCount;
    fc.messages = messageCount;
    fc.timestamps = timestampCount;
    fc.datestamps = datestampCount;
    
    write_file_count(&fc);
    print_file_count(&fc);
    
    // end timing the program
    clock_t endTime = clock();
    double totaltime = (double)(endTime - startTime)/CLOCKS_PER_SEC;
    printf("\nProcess time %f seconds\n", totaltime);
    
    
    return 0;
}
