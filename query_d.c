#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "location.h"
#include "message.h"
#include "timestamp.h"
#include "user.h"

int main(int argc, char **argv)
{
int i =0;
int count = 0;
int messageFound = 0;
int timestampID = 0;
int locationID = 0;
int userID = 0;
int last = 0;
int first = 0;
int mid = 0;
char nebraska[]  = "Nebraska";


    /* print usage if needed */
   if (argc != 5) {
        msgrintf(stderr, "Usage: %s total_message_number total_timestamp_number total_user_number total_location_number\n", argv[0]);
        exit(0);
    }
    
    /* get total record number */
    int total_message_number = atoi(argv[1]);
	int total_timestamp_number = atoi(argv[2]);
	int total_user_number = atoi(argv[3]);
	int total_location_number = atoi(argv[4]);

    struct timeval time_start, time_end;
    
    /* start time */
    gettimeofday(&time_start, NULL);
    
    for (i = 0; i < total_message_number; i++) {
        
        /* read the record from the file */
        message_t *messagePtr = read_message(i); 
		timestampID = messagePtr->timestampID;
		userID = messagePtr->userId;

		first = 0;
		last = total_timestamp_number;
		//check if hour is equal to 8
		while (first <= last){
			int mid = (first + last) /2;

			timestamp_t *timestampPtr = read_timestamp(mid);
			
			if (timestampID > timestampPtr->timestampID){
				first = mid + 1;
			}
			else if (timestampID > timestampPtr->timestampID){
				last = mid - 1;
			}
			else {
				if (timestampPtr->hour == 8 || (timestampPtr-> hour ==9 && timestampPtr->minute == 0)){
					last = total_user_number;
					first = 0;
					
					//find the userid so we can find the locationID
					while (first <= last){
						int mid = (first + last) /2;
												
						user_t *userPtr = read_user(mid);

						if (userID > userPtr->userId){
							first = mid + 1;
						}
						else if (userID > userPtr->userId){
							last = mid - 1;
						}
						else {
							if (userID == userPtr->userId){
								locationID = userPtr->locationId;
								
								first = 0;
								last = total_location_number;
								
								while (first <= last){
									int mid = (first + last) /2;
																		
									location_t *locationPtr = read_location(mid);
									if (locationID > locationPtr->locationId){
										first = mid + 1;
									}
									else if (locationID < locationPtr->locationId){
										last = mid - 1;
									}
									else {
										if (strcmp(locationPtr->state, nebraska) == 0){
											//TODO insert trippy michael function to increment a counter in a table of users that we will later go through to find the max user
											count += 1;
										}
									}			
								free_location(locationPtr);
								}
							}
						}
						free_user(userPtr);
					}
				}
			}
			free_timestamp(timestampPtr);
		}
		free_message(messagePtr);

    }    
        
    printf("count is %d", count);
    /* end time */
    gettimeofday(&time_end, NULL);
    
    float totaltime = (time_end.tv_sec - time_start.tv_sec)
                    + (time_end.tv_usec - time_start.tv_usec) / 1000000.0f;
                    
         
                    
    printf("\n\nProcess time %f seconds\n", totaltime);
    
    return 0;
}
