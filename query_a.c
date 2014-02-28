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
    int nebraskaCount;
    nebraskaCount = 0;
    int locationID;
    int mid;
    int first;
    int last;
    mid = 0;
    first = 0;
    last = 0;
    locationID = 0;
    char nebraska[]  = "Nebraska";

    /* print usage if needed */
    if (argc != 3) {
        fprintf(stderr, "Usage: %s total_user_number total_location_number\n", argv[0]);
        exit(0);
    }

    /* get total record number */
    int total_user_number = atoi(argv[1]);
    int total_location_number = atoi(argv[2]);

    struct timeval time_start, time_end;

    /* start time */
    gettimeofday(&time_start, NULL);
	
	/********* my code ********/
	bool validId[total_location_number];
	int j;
	for(j = 0; j < total_location_number; j++){
		validId[j] = false;
	}
	
	last = total_location_number - 1;
	while(first <= last){
		mid = (first + last) / 2;
		location_t *locPnt = read_location(mid);
		if(strcmp(locPnt->state, nebraska) == 0){
			validId[mid] = true;
			free_location(locPnt);
			for(j = mid - 1; j >= first; j--){
				locPnt = read_location(j);
				if(strcmp(locPnt->state, nebraska) == 0){
					validId[j] = true;
				}
				else{
					j = -1; //breaks the loop
				}
				free_location(locPnt);
			}
			for(j = mid + 1; j <= last; j++){
				locPnt = read_location(j);
				if(strcmp(locPnt->state, nebraska) == 0){
					validId[j] = true;
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
	
	for(j = 0; j < total_user_number; j++){
		user_t *user = read_user(j);
		if(validId[user->locationId]){
			nebraskaCount++;
		}
		free_location(user);
	}
	
	/********* end my code ********/

    printf("count is %d", nebraskaCount);
    /* end time */
    gettimeofday(&time_end, NULL);

    float totaltime = (time_end.tv_sec - time_start.tv_sec)
                    + (time_end.tv_usec - time_start.tv_usec) / 1000000.0f;



    printf("\n\nProcess time %f seconds\n", totaltime);

    return 0;
}