#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "record.h"
#include "user.h"
#include "message.h"
#include "city.h"
#include "state.h"
#include "timestamp.h"
#include "datestamp.h"
#include "file_count.h"

int main(int argc, char **argv)
{
    // time the program
    clock_t startTime = clock();
    struct timeval sysTimeStart, sysTimeEnd;
    gettimeofday(&sysTimeStart, NULL);
    
    // counters, etc.
    int nebraskaUserCount = 0,
        nebraskaStateId = -1,
        first, mid, last, j;
    char nebraskaStr[] = "Nebraska";
    
    // get file counts
    file_count_t *fc = read_file_count();
    int userCount = fc->users;
    int stateCount = fc->states;
    
    // binary search states to get Nebraska's ID
	first = 0;
    last = stateCount - 1;
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
    
	for (j = 0; j < userCount; j++)
    {
		user_t *user = read_user(j);
        if (user->stateId == nebraskaStateId)
        {
            nebraskaUserCount++;
        }
		free_user(user);
	}
    
    printf("Found %d users from %s (state id %d)\n", nebraskaUserCount, nebraskaStr, nebraskaStateId);
    
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
