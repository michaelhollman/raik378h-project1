#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>

#include "timestamp.h"
#include "int_node.h"
#include "bplus_roots.h"
#include "file_count.h"

int main(int argc, char **argv)
{
    // time the program
    struct timeval sysTimeStart, sysTimeEnd;
    gettimeofday(&sysTimeStart, NULL);

    bplus_roots_t *roots = read_bplus_roots();
    int timestampRoot = roots->timestamp;

    timestamp_t *startTime = (timestamp_t *)malloc(sizeof(timestamp_t));
    startTime->hour = 8;
    startTime->minute = 0;

    timestamp_t *endTime = (timestamp_t *)malloc(sizeof(timestamp_t));
    endTime->hour = 9;
    endTime->minute = 0;

    unsigned long startHash = hash_timestamp(startTime);
    unsigned long endHash = hash_timestamp(endTime);

    search_result_t *timestampSearchResult = search_bplus_range(timestampRoot, TABLE_TYPE_TIMESTAMP, startHash, endHash);
    print_search_result(timestampSearchResult);

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



    // end timing the program
    gettimeofday(&sysTimeEnd, NULL);
    float totalTime = (sysTimeEnd.tv_sec - sysTimeStart.tv_sec)
    + (sysTimeEnd.tv_usec - sysTimeStart.tv_usec) / 1000000.0f;
    printf("Process time %f seconds\n", totalTime);

    return 0;
}
