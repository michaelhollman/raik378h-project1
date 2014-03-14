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

    // arrays to keep track of valid times and counted users
	int validTimes[61]; //There can only be 61 times
	int validTimesCount = 0;
	bool countedUsers[userCount];
	for (int i = 0; i < userCount; i ++)
    {
		countedUsers[i] = false;
	}

    bplus_roots_t *roots = read_bplus_roots();
    int timestampRoot = roots->timestamp;
    int messageRoot = roots ->message;

    timestamp_t *startTime = (timestamp_t *)malloc(sizeof(timestamp_t));
    startTime->hour = 8;
    startTime->minute = 0;

    timestamp_t *endTime = (timestamp_t *)malloc(sizeof(timestamp_t));
    endTime->hour = 9;
    endTime->minute = 0;

    unsigned long startHash = hash_timestamp(startTime);
    unsigned long endHash = hash_timestamp(endTime);

    free_timestamp(endTime);
    free_timestamp(startTime);

    search_result_t *timestampSearchResult = search_bplus_range(timestampRoot, TABLE_TYPE_TIMESTAMP, startHash, endHash);
    print_search_result(timestampSearchResult);
    int timestamp_count = timestampSearchResult->count;
    if (timestamp_count != 61) {
        printf("We didn't find 61 separate minute id's. Did something go wrong?");
     //  return 0;
    }

    search_result_node_t *timestamp_search_node = timestampSearchResult-> head;

    for (int i = 0; i < timestamp_count; i ++){
       timestamp_t *timestamp = read_timestamp(timestamp_search_node->fileNumber);
       validTimes[i] = timestamp->timestampId;
       timestamp_search_node = timestamp_search_node->next;
       free_timestamp(timestamp);
    }
    int finalCount = 0;
    for (int i = 0; i < timestamp_count; i ++){
      search_result_t *message_search_result = search_bplus(messageRoot, TABLE_TYPE_MESSAGE,validTimes[i] );
      search_result_node_t *message_search_node = message_search_result-> head;
        for (int j = 0; j < message_search_result->count; j++){
            message_t *message = read_message(message_search_node ->fileNumber);
            if (!countedUsers[message->userId]){
                countedUsers[message->userId] = true;
                finalCount++;
            }
            free_message(message);
        }
            free_search_result(message_search_result);
    }
    printf("Number of matching users: %d\n", finalCount);

    // end timing the program
    gettimeofday(&sysTimeEnd, NULL);
    float totalTime = (sysTimeEnd.tv_sec - sysTimeStart.tv_sec)
    + (sysTimeEnd.tv_usec - sysTimeStart.tv_usec) / 1000000.0f;
    printf("Process time %f seconds\n", totalTime);

    return 0;
}
