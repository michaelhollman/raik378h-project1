#include <stdio.h>
#include <sys/time.h>

#include "record.h"
#include "user.h"
#include "message.h"
#include "city.h"
#include "state.h"
#include "timestamp.h"
#include "datestamp.h"
#include "file_count.h"
#include "int_node.h"
#include "bplus_roots.h"

int main(int argc, char **argv)
{
    // time the program
    struct timeval sysTimeStart, sysTimeEnd;
    gettimeofday(&sysTimeStart, NULL);
    
    int i;
    // open file count information
    file_count_t *fc = read_file_count();
    
    // keep track of roots
    bplus_roots_t bpr;
    
    // users
    {
        printf("\n");
        printf("Making user B+ tree with %d users\n", fc->users);
        
        // time this section
        struct timeval startSysTimeSub, endSysTimeSub;
        gettimeofday(&startSysTimeSub, NULL);
        
        // create root
        int_node_t root;
        root.next = -1;
        root.previous = -1;
        root.tableType = TABLE_TYPE_USER;
        root.nodeType = NODE_TYPE_LEAF;
        root.count = 0;
        root.firstFile = -1;
        write_node(0, &root);
        
        int rootFileNum = 0;
        
        for (i = 0; i < fc->users; i++)
        {
            user_t *user = read_user(i);
            rootFileNum = insert_node(rootFileNum, TABLE_TYPE_USER, user->stateId, i);
            free_user(user);
        }
        
        bpr.user = rootFileNum;
        
        // end timing this section
        gettimeofday(&endSysTimeSub, NULL);
        float totalTime = (endSysTimeSub.tv_sec - startSysTimeSub.tv_sec)
        + (endSysTimeSub.tv_usec - startSysTimeSub.tv_usec) / 1000000.0f;
        printf("B+ tree creation time:  %f seconds\n", totalTime);
    }
    
    // cities
    {
        printf("\n");
        printf("Making city B+ tree with %d cities\n", fc->cities);
        
        // time this section
        struct timeval startSysTimeSub, endSysTimeSub;
        gettimeofday(&startSysTimeSub, NULL);
        
        // create root
        int_node_t root;
        root.next = -1;
        root.previous = -1;
        root.tableType = TABLE_TYPE_CITY;
        root.nodeType = NODE_TYPE_LEAF;
        root.count = 0;
        root.firstFile = -1;
        write_node(0, &root);
        
        int rootFileNum = 0;
        
        for (i = 0; i < fc->cities; i++)
        {
            city_t *city = read_city(i);
            rootFileNum = insert_node(rootFileNum, TABLE_TYPE_CITY, city->stateId, i);
            free_city(city);
        }
        
        bpr.city = rootFileNum;
        
        // end timing this section
        gettimeofday(&endSysTimeSub, NULL);
        float totalTime = (endSysTimeSub.tv_sec - startSysTimeSub.tv_sec)
        + (endSysTimeSub.tv_usec - startSysTimeSub.tv_usec) / 1000000.0f;
        printf("B+ tree creation time:  %f seconds\n", totalTime);
    }
    
    //states
    {
        printf("\n");
        printf("Making state B+ tree with %d states\n", fc->states);
        
        // time this section
        struct timeval startSysTimeSub, endSysTimeSub;
        gettimeofday(&startSysTimeSub, NULL);
        
        // create root
        int_node_t root;
        root.next = -1;
        root.previous = -1;
        root.tableType = TABLE_TYPE_STATE;
        root.nodeType = NODE_TYPE_LEAF;
        root.count = 0;
        root.firstFile = -1;
        write_node(0, &root);
        
        int rootFileNum = 0;
        
        for (i = 0; i < fc->states; i++)
        {
            state_t *state = read_state(i);
            rootFileNum = insert_node(rootFileNum, TABLE_TYPE_STATE, (int) hash_state(state), i);
            free_state(state);
        }
        
        bpr.state = rootFileNum;
        
        // end timing this section
        gettimeofday(&endSysTimeSub, NULL);
        float totalTime = (endSysTimeSub.tv_sec - startSysTimeSub.tv_sec)
        + (endSysTimeSub.tv_usec - startSysTimeSub.tv_usec) / 1000000.0f;
        printf("B+ tree creation time:  %f seconds\n", totalTime);
    }
    
    // messages
    {
        printf("\n");
        printf("Making message B+ tree with %d messages\n", fc->messages);
        
        // time this section
        struct timeval startSysTimeSub, endSysTimeSub;
        gettimeofday(&startSysTimeSub, NULL);
        
        // create root
        int_node_t root;
        root.next = -1;
        root.previous = -1;
        root.tableType = TABLE_TYPE_MESSAGE;
        root.nodeType = NODE_TYPE_LEAF;
        root.count = 0;
        root.firstFile = -1;
        write_node(0, &root);
        
        int rootFileNum = 0;
        
        for (i = 0; i < fc->messages; i++)
        {
            message_t *message = read_message(i);
            rootFileNum = insert_node(rootFileNum, TABLE_TYPE_MESSAGE, message->timestampId, i);
            free_message(message);
        }
        
        bpr.message = rootFileNum;
        
        // end timing this section
        gettimeofday(&endSysTimeSub, NULL);
        float totalTime = (endSysTimeSub.tv_sec - startSysTimeSub.tv_sec)
        + (endSysTimeSub.tv_usec - startSysTimeSub.tv_usec) / 1000000.0f;
        printf("B+ tree creation time:  %f seconds\n", totalTime);
    }
    
    // timestamps
    {
        printf("\n");
        printf("Making timestamp B+ tree with %d timestamps\n", fc->timestamps);
        
        // time this section
        struct timeval startSysTimeSub, endSysTimeSub;
        gettimeofday(&startSysTimeSub, NULL);
        
        // create root
        int_node_t root;
        root.next = -1;
        root.previous = -1;
        root.tableType = TABLE_TYPE_TIMESTAMP;
        root.nodeType = NODE_TYPE_LEAF;
        root.count = 0;
        root.firstFile = -1;
        write_node(0, &root);
        
        int rootFileNum = 0;
        
        for (i = 0; i < fc->timestamps; i++)
        {
            timestamp_t *timestamp = read_timestamp(i);
            rootFileNum = insert_node(rootFileNum, TABLE_TYPE_TIMESTAMP, (int) hash_timestamp(timestamp), i);
            free_timestamp(timestamp);
        }
        
        bpr.timestamp = rootFileNum;
        
        // end timing this section
        gettimeofday(&endSysTimeSub, NULL);
        float totalTime = (endSysTimeSub.tv_sec - startSysTimeSub.tv_sec)
        + (endSysTimeSub.tv_usec - startSysTimeSub.tv_usec) / 1000000.0f;
        printf("B+ tree creation time:  %f seconds\n", totalTime);
    }
    
    // datestamps
    {
        printf("\n");
        printf("Making datestamp B+ tree with %d datestamps\n", fc->datestamps);
        
        // time this section
        struct timeval startSysTimeSub, endSysTimeSub;
        gettimeofday(&startSysTimeSub, NULL);
        
        
        // create root
        int_node_t root;
        root.next = -1;
        root.previous = -1;
        root.tableType = TABLE_TYPE_DATESTAMP;
        root.nodeType = NODE_TYPE_LEAF;
        root.count = 0;
        root.firstFile = -1;
        write_node(0, &root);
        
        int rootFileNum = 0;
        
        for (i = 0; i < fc->datestamps; i++)
        {
            datestamp_t *datestamp = read_datestamp(i);
            rootFileNum = insert_node(rootFileNum, TABLE_TYPE_DATESTAMP, (int) hash_datestamp(datestamp), i);
            free_datestamp(datestamp);
        }
        
        bpr.datestamp = rootFileNum;
        
        // end timing this section
        gettimeofday(&endSysTimeSub, NULL);
        float totalTime = (endSysTimeSub.tv_sec - startSysTimeSub.tv_sec)
        + (endSysTimeSub.tv_usec - startSysTimeSub.tv_usec) / 1000000.0f;
        printf("B+ tree creation time:  %f seconds\n", totalTime);
    }
    
    free_file_count(fc);
    
    printf("\n");
    
    print_bplus_roots(&bpr);
    write_bplus_roots(&bpr);
    
    // end timing the program
    gettimeofday(&sysTimeEnd, NULL);
    float totalTime = (sysTimeEnd.tv_sec - sysTimeStart.tv_sec)
    + (sysTimeEnd.tv_usec - sysTimeStart.tv_usec) / 1000000.0f;
    printf("Process time %f seconds\n", totalTime);
    
    return 0;
}