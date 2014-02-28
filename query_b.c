#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>

#include "user.h"
#include "message.h"
#include "location.h"
#include "timestamp.h"

int main(int argc, char **argv)
{
int i;
int timeCount = 0;
int timestampID = 0;
int userID = 0;
int last = 0;
int first = 0;
int mid = 0;


    /* print usage if needed */

    if (argc != 4) {
        fprintf(stderr, "Usage: %s total_message_number total_timestamp_number total_user_number\n", argv[0]);
        exit(0);
    }

    /* get total record number */
    int total_message_number = atoi(argv[1]);
	int total_timestamp_number = atoi(argv[2]);
	int total_user_number = atoi(argv[3]);

    struct timeval time_start, time_end;

    /* start time */
    gettimeofday(&time_start, NULL);

	bool validTime[total_timestamp_number];
	bool validUser[total_user_number];

	for (i = 0; i < total_user_number; i ++){
		validUser[i] = false;
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
			if (tsp->hour == 8 || (tsp-> hour ==9 && tsp->minute == 0)){
					timeCount +=1;
			}
		}
		free_timestamp(tsp);
	}


	for (i = mid; i < total_timestamp_number; i++){
		tsp = read_timestamp(i);
		if (tsp->hour == 8 || (tsp-> hour ==9 && tsp->minute == 0)){
			 validTime[i] = true;
		}
		else {
			validTime[i] = false;
		}
		free_timestamp(tsp);

	}

	for (i = mid-1; i >= 0; i--){
		tsp = read_timestamp(i);
		if (tsp->hour == 8 || (tsp-> hour ==9 && tsp->minute == 0)){
			 validTime[i] = true;
		}
		else {
			validTime[i] = false;
		}
		free_timestamp(tsp);
	}

    for (i = 0; i < total_message_number; i++) {
        /* read the record from the file */
        message_t *msgp = read_message(i);
		timestampID = msgp->timestampId;
		userID = msgp->userId;

		if (validTime[timestampID]){
			if (validUser[userID]){
				timeCount ++;
			}
			else{
              validUser[userID] = true;
			}
		}

		free_message(msgp);
    }

    printf("count is %d", timeCount);
    /* end time */
    gettimeofday(&time_end, NULL);

    float totaltime = (time_end.tv_sec - time_start.tv_sec)
                    + (time_end.tv_usec - time_start.tv_usec) / 1000000.0f;



    printf("\n\nProcess time %f seconds\n", totaltime);

    return 0;
}
