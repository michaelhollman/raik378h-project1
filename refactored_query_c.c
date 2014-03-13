#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>

#include "user.h"
#include "message.h"
#include "state.h"
#include "timestamp.h"
#include "file_count.h"

int main(int argc, char **argv)
{
    // time the program
    struct timeval sysTimeStart, sysTimeEnd;
    gettimeofday(&sysTimeStart, NULL);
    
    int nebraskaStateId, first, last, mid, i, j, k,
    finalCount = 0;
    char nebraskaStr[]  = "Nebraska";

    // get file counts
    file_count_t *fc = read_file_count();
    int userCount = fc->users;
    int stateCount = fc->states;
	int messageCount = fc->messages;
	int timestampCount = fc->timestamps;
    free_file_count(fc);
    
	// arrays to keep track of valid times and counted users
	int validTimes[61];
	int validTimesCount = 0;
    bool validUsers[userCount];
    for(i = 0; i < userCount; i++){
		validUsers[i] = false;
	}
    
    // binary search states to get Nebraska's ID
	first = 0;
    last = stateCount - 1;
    nebraskaStateId = -1;
	while (first <= last && nebraskaStateId == -1)
    {
		mid = (first + last) / 2;
		state_t *state = read_state(mid);
        
		if (strcmp(state->name, nebraskaStr) == 0)
        {
            nebraskaStateId = state->stateId;
		}
		else if (strcmp(state->name, nebraskaStr) < 0)
        {
			first = mid + 1;
		}
		else
        {
			last = mid - 1;
		}
        
        free_state(state);
	}
    
    first = 0;
	last = userCount - 1;
	while(first <= last)
    {
		mid = (first + last) / 2;
		user_t *user = read_user(mid);
        if (user->stateId == nebraskaStateId)
        {
            validUser[user->userId] = true;
			last = first - 1;
        }
		else if(user->stateId < nebraskaStateId)
		{
			first = mid + 1;
		}
		else
		{
			last = mid - 1;
		}
		free_user(user);
	}
	
	for(i = mid + 1; i < userCount; i++)
	{
		user_t *user = read_user(mid);
        if (user->stateId == nebraskaStateId)
        {
            validUser[user->userId] = true;
        }
		else
		{
			i = userCount;
		}
		free_user(user);
	}
	for(i = mid - 1; i >= 0; i--)
	{
		user_t *user = read_user(mid);
        if (user->stateId == nebraskaStateId)
        {
            validUser[user->userId] = true;
        }
		else
		{
			i = -1;
		}
		free_user(user);
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
	
	for (i = 0; i < validTimesCount; i++) {
		k = validTimes[i];
		first = 0;
		last = messageCount - 1;
		while(first <= last){
			mid = (first + last) / 2;
			message_t *msgp = read_message(mid);
			if(msgp->timestampId == k){
				if(validUsers[msgp->userId]){
					validUsers[msgp->userId] = false;
					finalCount++;
				}
				last = first - 1;
			}
			else if(msgp->timestampId < k){
				first = mid + 1;
			}
			else{
				last = mid - 1;
			}
			free_message(msgp);
		}
		for(j = mid + 1; j < messageCount; j++){
			message_t *msgp = read_message(j);
			if(msgp->timestampId == k){
				if(validUsers[msgp->userId]){
					countedUsers[msgp->userId] = false;
					finalCount++;
				}
			}
			else{
				j = messageCount;
			}
			free_message(msgp);
		}
		for(j = mid - 1; j >= 0; j--){
			message_t *msgp = read_message(j);
			if(msgp->timestampId == k){
				if(validUsers[msgp->userId]){
					validUsers[msgp->userId] = false;
					finalCount++;
				}
			}
			else{
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