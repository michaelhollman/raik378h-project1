#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>

#include "record.h"
#include "user.h"
#include "message.h"
#include "location.h"
#include "timestamp.h"

int main(int argc, char **argv)
{
    int count;
    count = 0;
    int locationID;
    int mid;
    int first;
    int last;
    int i;
    mid = 0;
    first = 0;
    last = 0;
    locationID = 0;
    char nebraska[]  = "Nebraska";

    /* print usage if needed */
    if (argc != 5) {
        fprintf(stderr, "Usage: %s total_user_number total_location_number total_message_number total_timestamp_number\n", argv[0]);
        exit(0);
    }

    /* get total record number */
    int total_user_number = atoi(argv[1]);
    int total_location_number = atoi(argv[2]);
	int total_message_number = atoi(argv[3]);
	int total_timestamp_number = atoi(argv[4]);

    struct timeval time_start, time_end;

    /* start time */
    gettimeofday(&time_start, NULL);

	/********* my code ********/
	bool validLocationId[total_location_number];
	int j;
	for(j = 0; j < total_location_number; j++){
		validLocationId[j] = false;
	}

	last = total_location_number - 1;
	while(first <= last){
		mid = (first + last) / 2;
		location_t *locPnt = read_location(mid);
		if(strcmp(locPnt->state, nebraska) == 0){
			validLocationId[mid] = true;
			free_location(locPnt);
			for(j = mid - 1; j >= first; j--){
				locPnt = read_location(j);
				if(strcmp(locPnt->state, nebraska) == 0){
					validLocationId[j] = true;
				}
				else{
					j = -1; //breaks the loop
				}
				free_location(locPnt);
			}
			for(j = mid + 1; j <= last; j++){
				locPnt = read_location(j);
				if(strcmp(locPnt->state, nebraska) == 0){
					validLocationId[j] = true;
				}
				else{
					j = last + 1; //breaks the loop
				}
				free_location(locPnt);
			}
		}
		else if(strcmp(locPnt->state, nebraska) < 0){
			first = mid + 1;
			free_location(locPnt);
		}
		else{
			last = mid - 1;
			free_location(locPnt);
		}
	}

	int validUserID[total_user_number];
	for(j = 0; j < total_user_number; j++){
		user_t *user = read_user(j);
		if(validLocationId[user->locationId]){
			validUserID[user->userId] = 0;
		}
		else{
			validUserID[user->userId] = -1;
		}
		free_user(user);
	}

	bool validTime[total_timestamp_number];
	for (i = 0; i < total_timestamp_number; i ++){
		validTime[i] = false;
	}

	first = 0;
	last = total_timestamp_number;
	timestamp_t *tsp;

	while (first <= last){
		mid = (first + last) /2;
		tsp = read_timestamp(mid);

		if (tsp->hour < 8){
			first = mid + 1;
		}
		else if (tsp->hour > 9 || tsp->hour ==9 && tsp-> minute > 0 ){
			last = mid - 1;
		}
		else {
			first = last + 1;
		}
		free_timestamp(tsp);
	}


	for (i = mid; i < total_timestamp_number; i++){
		tsp = read_timestamp(i);
		if (tsp->hour == 8 || (tsp-> hour ==9 && tsp->minute == 0)){
			 validTime[i] = true;
		}
		else{
            i = total_timestamp_number;
		}
		free_timestamp(tsp);

	}

	for (i = mid-1; i >= 0; i--){
		tsp = read_timestamp(i);
		if (tsp->hour == 8 || (tsp-> hour ==9 && tsp->minute == 0)){
			 validTime[i] = true;
		}
		else{
            i = -1;
		}
		free_timestamp(tsp);
	}


	for(j = 0; j < total_message_number; j++){
		message_t *message = read_message(j);
		if(validTime[message->timestampId]){
			if(validUserID[message->userId] > -1){
				validUserID[message->userId]++;
			}
		}
		free_message(message);
	}

	int max = 0;
	int maxId = -1;
	for(j = 0; j < total_user_number; j++){
		if(validUserID[j] > max){
			max = validUserID[j];
			maxId = j;
		}
	}

	/********* end my code ********/

    printf("id of the max nebraskan 8 to 9 sender is %d", maxId);
    /* end time */
    gettimeofday(&time_end, NULL);

    float totaltime = (time_end.tv_sec - time_start.tv_sec)
                    + (time_end.tv_usec - time_start.tv_usec) / 1000000.0f;



    printf("\n\nProcess time %f seconds\n", totaltime);

    return 0;
}
