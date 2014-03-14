#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>

#include "timestamp.h"
#include "int_node.h"
#include "bplus_roots.h"
#include "file_count.h"
#include "message.h"

int main(int argc, char **argv)
{
    // time the program
    struct timeval sysTimeStart, sysTimeEnd;
    gettimeofday(&sysTimeStart, NULL);
    
    // get file counts
    file_count_t *fc = read_file_count();
    int messageCount = fc->messages;
	int timestampCount = fc->timestamps;
    int userCount = fc->users;
    free_file_count(fc);
    
    // get b+ roots
    bplus_roots_t *bpr = read_bplus_roots();
    int timestampRoot = bpr->timestamp;
    int messageRoot = bpr->message;
    free_bplus_roots(bpr);
    
    // array to keep track of counted users
	bool countedUsers[userCount];
	for (int i = 0; i < userCount; i ++)
    {
		countedUsers[i] = false;
	}
    
    // timestamps are hashed into ints as HHMM
    int startTime = 800;
    int endTime = 900;
    
    // query for timestamps between 8 and 9 (incusive)
    search_result_t *timestampSearchResult = search_bplus_range(timestampRoot, TABLE_TYPE_TIMESTAMP, startTime, endTime);
    if (timestampSearchResult->count != 61)
    {
        printf("WARNING: didn't find 61 separate timestamps. Did something go wrong?\n");
    }
    
    // convert linked list of timestamp file numbers into array of timestamp ids
    int validTimeIds[timestampSearchResult->count];
    search_result_node_t *tsSearchNode = timestampSearchResult->head;
    for (int i = 0; i < timestampSearchResult->count; i ++)
    {
        timestamp_t *timestamp = read_timestamp(tsSearchNode->fileNumber);
        validTimeIds[i] = timestamp->timestampId;
        tsSearchNode = tsSearchNode->next;
        free_timestamp(timestamp);
    }
    
    // for each timestamp id, query the message tree to get messages with that timestamp id
    int finalUserCount = 0;
    for (int i = 0; i < timestampSearchResult->count; i ++)
    {
        search_result_t *messageSearchResult = search_bplus(messageRoot, TABLE_TYPE_MESSAGE, validTimeIds[i]);
        search_result_node_t *mSearchNode = messageSearchResult-> head;
        
        // loop over all the matching messages
        for(; mSearchNode != NULL; mSearchNode = mSearchNode->next)
        {
            message_t *message = read_message(mSearchNode->fileNumber);
            if (!(countedUsers[message->userId]))
            {
                countedUsers[message->userId] = true;
                finalUserCount++;
            }
            free_message(message);
        }
        free_search_result(messageSearchResult);
    }
    
    free_search_result(timestampSearchResult);
    
    printf("Number of matching users: %d\n", finalUserCount);
    
    // end timing the program
    gettimeofday(&sysTimeEnd, NULL);
    float totalTime = (sysTimeEnd.tv_sec - sysTimeStart.tv_sec)
    + (sysTimeEnd.tv_usec - sysTimeStart.tv_usec) / 1000000.0f;
    printf("Process time %f seconds\n", totalTime);
    
    return 0;
}
