#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>

#include "user.h"
#include "message.h"
#include "timestamp.h"
#include "file_count.h"

int main(int argc, char **argv)
{
    // time the program
    struct timeval sysTimeStart, sysTimeEnd;
    gettimeofday(&sysTimeStart, NULL);
    
    int i, first, mid, last, j, k;
    
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
	int validTimes[61]; //There can only be 61 times
	int validTimesCount = 0;
	bool countedUsers[userCount];
	for (i = 0; i < userCount; i ++)
    {
		countedUsers[i] = false;
	}
    
    // binary search for a valid timestamp
	first = 0;
	last = timestampCount - 1;
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
            validTimes[validTimesCount] = tsp->timestampId;
			validTimesCount++;
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
    
    // binary search through all messages
    for (i = 0; i < validTimesCount; i++)
    {
		k = validTimes[i];
		first = 0;
		last = messageCount - 1;
		while(first <= last)
        {
			mid = (first + last) / 2;
			message_t *msgp = read_message(mid);
			if(msgp->timestampId == k)
            {
				if(!countedUsers[msgp->userId])
                {
					countedUsers[msgp->userId] = true;
					finalCount++;
				}
				last = first - 1;
			}
			else if(msgp->timestampId < k)
            {
				first = mid + 1;
			}
			else
            {
				last = mid - 1;
			}
			free_message(msgp);
		}
		for(j = mid + 1; j < messageCount; j++)
        {
			message_t *msgp = read_message(j);
			if(msgp->timestampId == k)
            {
				if(!countedUsers[msgp->userId])
                {
					countedUsers[msgp->userId] = true;
					finalCount++;
				}
			}
			else
            {
				j = messageCount;
			}
			free_message(msgp);
		}
		for(j = mid - 1; j >= 0; j--)
        {
			message_t *msgp = read_message(j);
			if(msgp->timestampId == k)
            {
				if(!countedUsers[msgp->userId])
                {
					countedUsers[msgp->userId] = true;
					finalCount++;
				}
			}
			else
            {
				j = -1;
			}
			free_message(msgp);
		}
    }
    
    printf("Number of matching users: %d\n", finalCount);
    
    // end timing the program
    gettimeofday(&sysTimeEnd, NULL);
    float totalTime = (sysTimeEnd.tv_sec - sysTimeStart.tv_sec)
    + (sysTimeEnd.tv_usec - sysTimeStart.tv_usec) / 1000000.0f;
    printf("Process time %f seconds\n", totalTime);
    
    return 0;
}