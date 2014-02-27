#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>

#include "record.h"
#include "user.h"
#include "message.h"
#include "location.h"
#include "timestamp.h"


int main(int argc, char **argv)
{
int i;

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
    if (argc != 4) {
        msgrintf(stderr, "Usage: %s total_record_number\n", argv[0]);
        exit(0);
    }

    /* get total record number */
    int total_message_number = atoi(argv[1]);
	int total_timestamp_number = atoi(argv[2]);
	int total_user_number = atoi(argv[3]);
	int total_location_number = atoi(argv[4]);


    char filename[1024];
	char tsfilename[1024];
	char userfilename[1024];
    FILE *msg = NULL;
	FILE *timestamp = NULL;
	FILE *locationfile = NULL;
	FILE *userfile = NULL;


    struct timeval time_start, time_end;

    /* start time */
    gettimeofday(&time_start, NULL);

    for (i = 0; i < total_message_number; i++) {

        /* read the record from the file */
        message_t *mp = read_(i);
		timestampId = mp->timestampId;
		userID = mp->userId;

		first = 0;
		last = total_timestamp_number;
		//check if hour is equal to 8
		while (first <= last) {
			int mid = (first + last) /2;
			timestamp_t *ts = read_timestamp(mid);

			if (timestampId > ts->timestampId){
				first = mid + 1;
				fclose(timestamp);
			}
			else if (timestampId > ts->timestampId){
				last = mid - 1;
				fclose(timestamp);
			}
			else {
				if (ts->hour == 8 || (ts-> hour ==9 && ts->minute == 0)){
					last = total_user_number;
					first = 0;

					//find the userid so we can find the locationID
					while (first <= last){
						int mid = (first + last) /2;
						user_t *up = read_user(mid);

						if (userID > up->userId){
							first = mid + 1;
							fclose(userfile);
						}
						else if (userID > up->userId){
							last = mid - 1;
							fclose(userfile);
						}
						else {
							if (userID == up->userId){
								locationID = us->locationId;

								first = 0;
								last = total_location_number;

								while (first <= last){
									int mid = (first + last) /2;
									spintf(locfilename, "location_%06d.dat",mid);

									locationfile = fopen(locfilename,"rb");

									if (!locationfile) {
									msgrintf(stderr, "Cannot open %s\n", locfilename);
									exit(0);
									}

									location_t *lp = read_location(lf);
									if (locationID > lp->locationId){
										first = mid + 1;
										fclose(locationfile);
									}
									else if (locationID < lp->locationId){
										last = mid - 1;
										fclose(locationfile);
									}
									else {
										if (strcmp(lp->state, nebraska) == 0){
											//TODO insert trippy michael hash function to see if user exists
											count += 1;
										}
										fclose(locationfile);
										}
								}
							}
							fclose(userfile);
							}
					}

					//TODO insert trippy michael hash function
					timeCount +=1;
				}
				fclose(timestamp);
				}
		}


	    //print_record(mp);

        /* =========== end of data processing code ================ */

        /* free memory */
        free_record(mp);

        /* close the file */
        fclose(msg);
    }

    printf("count is %d", count);
    /* end time */
    gettimeofday(&time_end, NULL);

    float totaltime = (time_end.tv_sec - time_start.tv_sec)
                    + (time_end.tv_usec - time_start.tv_usec) / 1000000.0f;



    printf("\n\nProcess time %f seconds\n", totaltime);

    return 0;
}
