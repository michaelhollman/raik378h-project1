#include <stdio.h>
#include <stdlib.h>
<<<<<<< Updated upstream
#include <sys/times.h>

#include "record.h"
#include "user.h"
#include "message.h"
#include "location.h"
#include "timestamp.h"
=======
#include <sys/time.h>
>>>>>>> Stashed changes

#include "location.h"
#include "message.h"
#include "timestamp.h"
#include "user.h"

int main(int argc, char **argv)
{
int i =0;
int count = 0;
int messageFound = 0;
int timestampId = 0;
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
<<<<<<< Updated upstream


    char filename[1024];
	char tsfilename[1024];
	char userfilename[1024];
    FILE *msg = NULL;
	FILE *timestamp = NULL;
	FILE *locationfile = NULL;
	FILE *userfile = NULL;


=======

>>>>>>> Stashed changes
    struct timeval time_start, time_end;

    /* start time */
    gettimeofday(&time_start, NULL);

    for (i = 0; i < total_message_number; i++) {
<<<<<<< Updated upstream

        /* read the record from the file */
        message_t *mp = read_(i);
		timestampId = mp->timestampId;
		userID = mp->userId;
=======
        
        /* read the record from the file */
        message_t *messagePtr = read_message(i); 
		timestampID = messagePtr->timestampID;
		userID = messagePtr->userId;
>>>>>>> Stashed changes

		first = 0;
		last = total_timestamp_number;
		//check if hour is equal to 8
		while (first <= last) {
			int mid = (first + last) /2;
<<<<<<< Updated upstream
			timestamp_t *ts = read_timestamp(mid);

			if (timestampId > ts->timestampId){
=======

			timestamp_t *timestampPtr = read_timestamp(mid);
			
			if (timestampID > timestampPtr->timestampID){
>>>>>>> Stashed changes
				first = mid + 1;
			}
<<<<<<< Updated upstream
			else if (timestampId > ts->timestampId){
=======
			else if (timestampID > timestampPtr->timestampID){
>>>>>>> Stashed changes
				last = mid - 1;
			}
			else {
				if (timestampPtr->hour == 8 || (timestampPtr-> hour ==9 && timestampPtr->minute == 0)){
					last = total_user_number;
					first = 0;

					//find the userid so we can find the locationID
					while (first <= last){
						int mid = (first + last) /2;
<<<<<<< Updated upstream
						user_t *up = read_user(mid);
=======
												
						user_t *userPtr = read_user(mid);
>>>>>>> Stashed changes

						if (userID > userPtr->userId){
							first = mid + 1;
						}
						else if (userID > userPtr->userId){
							last = mid - 1;
						}
						else {
<<<<<<< Updated upstream
							if (userID == up->userId){
								locationID = us->locationId;

=======
							if (userID == userPtr->userId){
								locationID = userPtr->locationId;
								
>>>>>>> Stashed changes
								first = 0;
								last = total_location_number;

								while (first <= last){
									int mid = (first + last) /2;
<<<<<<< Updated upstream
									spintf(locfilename, "location_%06d.dat",mid);

									locationfile = fopen(locfilename,"rb");

									if (!locationfile) {
									msgrintf(stderr, "Cannot open %s\n", locfilename);
									exit(0);
									}

									location_t *lp = read_location(lf);
									if (locationID > lp->locationId){
=======
																		
									location_t *locationPtr = read_location(mid);
									if (locationID > locationPtr->locationId){
>>>>>>> Stashed changes
										first = mid + 1;
									}
									else if (locationID < locationPtr->locationId){
										last = mid - 1;
									}
									else {
										if (strcmp(locationPtr->state, nebraska) == 0){
											//TODO insert trippy michael hash function to see if userID has already been counted 
											count += 1;
										}
									}
								}
							}
						}
					}
<<<<<<< Updated upstream

					//TODO insert trippy michael hash function
					timeCount +=1;
				}
				fclose(timestamp);
=======
>>>>>>> Stashed changes
				}
			}
		}
<<<<<<< Updated upstream


	    //print_record(mp);

        /* =========== end of data processing code ================ */

        /* free memory */
        free_record(mp);

        /* close the file */
        fclose(msg);
    }

=======
        free_user(userPtr);
		free_message(messagePtr);
		free_timestamp(timestampPtr);
		free_location(locationPtr);
    }    
        
>>>>>>> Stashed changes
    printf("count is %d", count);
    /* end time */
    gettimeofday(&time_end, NULL);

    float totaltime = (time_end.tv_sec - time_start.tv_sec)
                    + (time_end.tv_usec - time_start.tv_usec) / 1000000.0f;



    printf("\n\nProcess time %f seconds\n", totaltime);

    return 0;
}
