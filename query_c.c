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
    clock_t startTime = clock();
    struct timeval sysTimeStart, sysTimeEnd;
    gettimeofday(&sysTimeStart, NULL);
    
    
    //    int count;
    //    count = 0;
    //    int locationID;
    //    int mid;
    //    int first;
    //    int last;
    //    int i;
    //    mid = 0;
    //    first = 0;
    //    last = 0;
    //    locationID = 0;
    //    char nebraska[]  = "Nebraska";
    
    
    
    int nebraskaStateId, first, last, mid, i,
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
	bool validTimes[timestampCount];
    bool validUsers[userCount];
    for (i = 0; i < timestampCount; i ++)
    {
		validTimes[i] = false;
	}
    // user bool array initialized later
    
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
    
    
    //	last = stateCount - 1;
    //	while(first <= last){
    //		mid = (first + last) / 2;
    //		location_t *locPnt = read_location(mid);
    //		if(strcmp(locPnt->state, nebraska) == 0){
    //			validLocationId[mid] = true;
    //			free_location(locPnt);
    //			for(j = mid - 1; j >= first; j--){
    //				locPnt = read_location(j);
    //				if(strcmp(locPnt->state, nebraska) == 0){
    //					validLocationId[j] = true;
    //				}
    //				else{
    //					j = -1; //breaks the loop
    //				}
    //				free_location(locPnt);
    //			}
    //			for(j = mid + 1; j <= last; j++){
    //				locPnt = read_location(j);
    //				if(strcmp(locPnt->state, nebraska) == 0){
    //					validLocationId[j] = true;
    //				}
    //				else{
    //					j = last + 1; //breaks the loop
    //				}
    //				free_location(locPnt);
    //			}
    //			last = first -1;
    //		}
    //		else if(strcmp(locPnt->state, nebraska) < 0){
    //			first = mid + 1;
    //			free_location(locPnt);
    //		}
    //		else{
    //			last = mid - 1;
    //			free_location(locPnt);
    //		}
    //	}
    
    
    // mark all users from Nebraska as valid, else invalid
    for (i = 0; i < userCount; i++)
    {
		user_t *user = read_user(i);
        validUsers[user->userId] = (user->stateId == nebraskaStateId);
        free_user(user);
	}
    
    
    //	bool validUserID[userCount];
    //	for(j = 0; j < userCount; j++){
    //		user_t *user = read_user(j);
    //		if(validLocationId[user->locationId]){
    //			validUserID[user->userId] = true;
    //		}
    //		else{
    //			validUserID[user->userId] = false;
    //		}
    //		free_user(user);
    //	}
    
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
    
    
    
    //	bool validTime[timestampCount];
    //	for (i = 0; i < timestampCount; i ++){
    //		validTime[i] = false;
    //	}
    //
    //	first = 0;
    //	last = timestampCount;
    //	timestamp_t *tsp;
    //
    //	while (first <= last){
    //		mid = (first + last) /2;
    //		tsp = read_timestamp(mid);
    //
    //		if (tsp->hour < 8){
    //			first = mid + 1;
    //		}
    //		else if (tsp->hour > 9 || tsp->hour ==9 && tsp-> minute > 0 ){
    //			last = mid - 1;
    //		}
    //		else {
    //			first = last + 1;
    //		}
    //		free_timestamp(tsp);
    //	}
    
    
    //	for (i = mid; i < timestampCount; i++){
    //		tsp = read_timestamp(i);
    //		if (tsp->hour == 8 || (tsp-> hour ==9 && tsp->minute == 0)){
    //			 validTime[i] = true;
    //		}
    //		else{
    //            i = timestampCount;
    //		}
    //		free_timestamp(tsp);
    //
    //	}
    //
    //	for (i = mid-1; i >= 0; i--){
    //		tsp = read_timestamp(i);
    //		if (tsp->hour == 8 || (tsp-> hour ==9 && tsp->minute == 0)){
    //			 validTime[i] = true;
    //		}
    //		else{
    //            i = -1;
    //		}
    //		free_timestamp(tsp);
    //	}
    
    
    // loop through all messages
	for(i = 0; i < messageCount; i++)
    {
		message_t *message = read_message(i);
		if(validTimes[message->timestampId] && validUsers[message->userId])
        {
            validUsers[message->userId] = false; // don't count user again
            finalCount++;
			
		}
		free_message(message);
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
