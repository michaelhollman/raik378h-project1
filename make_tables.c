#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "make_tables.h"
#include "record.h"
#include "user.h"
#include "message.h"
#include "timestamp.h"
#include "location.h"

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
    locationCount = 0,
    timestampCount = 0,
    messageCount = 0,
    i,j,k;
    
    
    // SET UP HASH TABLES FOR LOCATIONS AND TIMESTAMPS
    // locations
    location_node *locationHT[HASH_SIZE];
    for (i = 0; i < HASH_SIZE; i++)
    {
        locationHT[i] = malloc(sizeof(location_node));
        locationHT[i] = NULL;
    }
    
    // timestamps
    timestamp_node *timestampHT[HASH_SIZE];
    for (i = 0; i < HASH_SIZE; i++)
    {
        timestampHT[i] = malloc(sizeof(timestamp_node));
        timestampHT[i] = NULL;
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
        
        //read the record from the file
        record_t *record = read_record(fp);
        
//        printf("%s\n","just read record");
        
        
        // create location
        location_t location;
        // there's a few records where the location is \0, which strtok breaks on
        if (record->location[0] == '\0')
        {
            strncpy(location.city, "", TEXT_SHORT);
            strncpy(location.state, "", TEXT_SHORT);
        }
        else
        {
            char loc[TEXT_SHORT];
            strncpy(loc, record->location, TEXT_SHORT);
            strncpy(location.city, strtok(loc, ","), TEXT_SHORT);
            strncpy(location.state, strtok(NULL, ","), TEXT_SHORT);
            
        }
        
        
        
        
        // get locationId from hash if we have it already
        unsigned int locationHash = hash_location(&location) % HASH_SIZE;
        location_node *l;
        int locId = -1;
        for(l = locationHT[locationHash]; (l != NULL) && (locId != -1); l = l->next)
        {
            if (compare_locations(&location, &(l->location)) == 0)
            {
//                printf("%s\n","found existing location");
                locId = l->location.locationId;
            }
        }
        
        // assign locationId, add to hash table, and write file if we don't have it
        if (locId == -1)
        {
//            printf("%s\n","trying to add location");
            location.locationId = locationCount;
            locId = locationCount;
            write_location(locationCount, &location);
            locationCount++;
            
            l = malloc(sizeof(location_node));
            l->location = location;
            l->next = locationHT[locationHash];
            locationHT[locationHash] = l;
//            printf("%s\n","added location");
        }
        
        // create and write user
        user_t user;
        user.userId = record->id;
        user.locationId = locId;
        strncpy(user.name, record->name, TEXT_SHORT);
        write_user(userCount, &user);
        userCount++;
        
        
        // loop over messages
        for(j = 0; j < record->message_num; j++) {
            // create timestamp
            timestamp_t timestamp;
            timestamp.year = record->messages[j].year;
            timestamp.month = record->messages[j].month;
            timestamp.day = record->messages[j].day;
            timestamp.hour = record->messages[j].hour;
            timestamp.minute = record->messages[j].minute;
            
            // get timestampId from hash if we have it already
            unsigned int timestampHash = hash_timestamp(&timestamp) % HASH_SIZE;
            timestamp_node *t;
            int tsId = -1;
            for(t = timestampHT[timestampHash]; (t != NULL) && (tsId != -1); t = t->next)
            {
                if (compare_timestamps(&timestamp, &(t->timestamp)) == 0)
                {
//                    printf("%s\n","found existing timestamp");
                    tsId = t->timestamp.timestampId;
                }
            }
            
            // assign timestampId, add to hash table, and write file if we don't have it
            if (tsId == -1)
            {
//                printf("%s\n","trying to add timestamp");
                timestamp.timestampId = timestampCount;
                tsId = timestampCount;
                write_timestamp(timestampCount, &timestamp);
                timestampCount++;
                
                t = malloc(sizeof(timestamp_node));
                t->timestamp = timestamp;
                t->next = timestampHT[timestampHash];
                timestampHT[timestampHash] = t;
//                printf("%s\n","added timestamp");
            }
            
            //print_timestamp(&timestamp);
            
            
            message_t message;
            strncpy(message.text, record->messages[j].text, TEXT_LONG);
            message.userId = user.userId;
            message.timestampId = tsId;
            message.messageId = messageCount;
            
            write_message(messageCount, &message);
            messageCount++;
            
            //print_message(&message);
        }
        
        // free record
        free_record(record);
        // close the file
        fclose(fp);
        
        if (i % 500 == 0){
            printf("%d\n",i);
        }
    }
    // done processing all files
    
    // free location nodes
    location_node *lNode;
    for (i = 0; i < HASH_SIZE; i++)
    {
    	lNode = locationHT[i];
    	while (lNode != NULL)
    	{
    		location_node* tmp = lNode;
    		lNode = lNode->next;
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
    
    // end timing the program
    clock_t endTime = clock();
    double totaltime = (double)(endTime - startTime)/CLOCKS_PER_SEC;
    printf("\nProcess time %f seconds\n\n", totaltime);
    
    // stats
    printf("%-11s: %d\n","Users",userCount);
    printf("%-11s: %d\n","Locations",locationCount);
    printf("%-11s: %d\n","Messages",messageCount);
    printf("%-11s: %d\n","Timestamps",timestampCount);
    printf("%-11s: %d\n","Total",userCount + locationCount + messageCount + timestampCount);
    
    return 0;
}
