#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>

#include "user.h"
#include "state.h"
#include "file_count.h"

int main(int argc, char **argv)
{
    // time the program
    struct timeval sysTimeStart, sysTimeEnd;
    gettimeofday(&sysTimeStart, NULL);
    
    // counters, etc.
    int first, mid, last, i,
        nebraskaUserCount = 0,
        nebraskaStateId;
    char nebraskaStr[] = "Nebraska";
    
    // get file counts
    file_count_t *fc = read_file_count();
    int userCount = fc->users;
    int stateCount = fc->states;
    free_file_count(fc);
    
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
	
    // note, if we didn't find Nebraska, nebraskaStateId = -1
    first = 0;
	last = userCount - 1;
	while(first <= last)
    {
		mid = (first + last) / 2;
		user_t *user = read_user(mid);
        if (user->stateId == nebraskaStateId)
        {
            nebraskaUserCount++;
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
		user_t *user = read_user(i);
        if (user->stateId == nebraskaStateId)
        {
            nebraskaUserCount++;
        }
		else
		{
			i = userCount;
		}
		free_user(user);
	}
	for(i = mid - 1; i >= 0; i--)
	{
		user_t *user = read_user(i);
        if (user->stateId == nebraskaStateId)
        {
            nebraskaUserCount++;
        }
		else
		{
			i = -1;
		}
		free_user(user);
	}
    
    printf("Found %d users from %s (state id %d)\n", nebraskaUserCount, nebraskaStr, nebraskaStateId);
    
    // end timing the program
    gettimeofday(&sysTimeEnd, NULL);
    float totalTime = (sysTimeEnd.tv_sec - sysTimeStart.tv_sec)
    + (sysTimeEnd.tv_usec - sysTimeStart.tv_usec) / 1000000.0f;
    printf("Process time %f seconds\n", totalTime);
    
    return 0;
}