#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>
#include <string.h>

#include "user.h"
#include "message.h"
#include "timestamp.h"
#include "file_count.h"

int main(int argc, char **argv)
{
    // time the program
    clock_t startTime = clock();
    struct timeval sysTimeStart, sysTimeEnd;
    gettimeofday(&sysTimeStart, NULL);
    
    int i, first, mid, last;
    
    int finalCount = 0;
    int timestampID = 0;
    int userID = 0;

    // get file counts
    file_count_t *fc = read_file_count();
    int messageCount = fc->messages;
	int timestampCount = fc->timestamps;
    int userCount = fc->users;
    free_file_count(fc);
    
    // arrays to keep track of valid times and counted users
	bool validTimes[timestampCount];
	bool countedUsers[userCount];
	for (i = 0; i < timestampCount; i ++)
    {
		validTimes[i] = false;
	}
	for (i = 0; i < userCount; i ++)
    {
		countedUsers[i] = false;
	}

    // binary search for a valid timestamp
	first = 0;
	last = timestampCount;
    bool found = false;
	while (first <= last && !found)
    {
		mid = (first + last) / 2;
        timestamp_t *tsp = read_timestamp(mid);

		if (tsp->hour < 8)
        {
			first = mid + 1;
		}
		else if (tsp->hour > 9 || (tsp->hour == 9 && tsp->minute > 0))
        {
			last = mid - 1;
		}
		else // found
        {
            found = true;
        }
		free_timestamp(tsp);
	}
    
    // mark valid times above and below as valid
    int direction = 1;
    bool done = false;
	for (i = mid; i < timestampCount && !done; i += direction)
    {
		timestamp_t *tsp = read_timestamp(i);
		if (tsp->hour == 8 || (tsp->hour == 9 && tsp->minute == 0))
        {
            validTimes[tsp->timestampId] = true;
		}
		else if (direction == 1) //reset, switch directions
        {
            i = mid;
            direction = -1;
        }
        else
        {
            done = true;
		}
        free_timestamp(tsp);
	}

    // loop through all messages
    for (i = 0; i < messageCount; i++) {
        message_t *msgp = read_message(i);
        // if the message's time is valid and we haven't counted the user already...
		if (validTimes[msgp->timestampId] && !countedUsers[msgp->userId])
        {
            // mark user as counted, increment final count
            countedUsers[msgp->userId] = true;
            finalCount++;
		}
		free_message(msgp);
    }

    printf("Number of matching users: %d\n", finalCount);
    
    // end timing the program
    clock_t endTime = clock();
    double totaltime = (double)(endTime - startTime)/CLOCKS_PER_SEC;
    printf("\nProcess time %f seconds (time.h)\n", totaltime);
    gettimeofday(&sysTimeEnd, NULL);
    float totaltime2 = (sysTimeEnd.tv_sec - sysTimeStart.tv_sec)
    + (sysTimeEnd.tv_usec - sysTimeStart.tv_usec) / 1000000.0f;
    printf("Process time %f seconds (sys/time.h)\n", totaltime2);
    
    return 0;
}
