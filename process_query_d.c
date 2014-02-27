#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>

#include "record.h"


int main(int argc, char **argv)
{
int i;

int count = 0;
int messageFound = 0;
int timestampID = 0;
int locationID = 0;
int userID = 0;
int maxId = 0;
int maxCount = 0;
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
	FILE *timestamp = NULL:
	FILE *locationfile = NULL: 
	FILE *userfile = NULL; 
	
	
    struct timeval time_start, time_end;
    
    /* start time */
    gettimeofday(&time_start, NULL);
    
    for (i = 0; i < total_message_number; i++) {
        /* open the corresponding file */  
	        sprintf(filename, "message_%06d.dat", i);
    
        msg = fopen(filename,"rb");
    
        if (!msg) {
            msgrintf(stderr, "Cannot open %s\n", filename);
            exit(0);
        }
        
        /* read the record from the file */
        //record_t *rp = read_record(msg); TODO Cassey's read message
		timestampID = rp->timestampID;
		userID = ->userId;

		first = 0;
		last = total_timestamp_number;
		//check if hour is equal to 8
		while (first <= last){
			int mid = (first + last) /2;
			spintf(tsfilename, "timestamp_%06d.dat",mid);
		
			timestamp = fopen(tsfilename,"rb");
			if (!timestamp) {
            msgrintf(stderr, "Cannot open %s\n", tsfilename);
            exit(0);
			}
			
			timestamp_t *ts = read_timestamp(timestamp); TODO Cassey's read message
			if (timestampID > ts->timestampID){
				first = mid + 1;
				fclose(timestamp);
			}
			else if (timestampID > ts->timestampID){
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
						spintf(userfilename, "user_%06d.dat",mid);
					
						userfile = fopen(userfilename,"rb");
						if (!userfile) {
						msgrintf(stderr, "Cannot open %s\n", tsfilename);
						exit(0);
						}
						
						user_t *up = read_user(userfile);

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
								locationID = up->locationId;
								
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
									
									location_t *lp = read_location(locationfile); 
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
				
					//TODO insert function to store count for each user id 
				}
				fclose(timestamp);
				}
		}
		
    
        /* free memory */
        free_record(rp);
    
        /* close the file */
        fclose(msg);
    }    
    
	//TODO insert function to find maxID 
    
    printf("maxId is %d\n", maxId);
	printf("maxcount is %d", maxCount);
    /* end time */
    gettimeofday(&time_end, NULL);
    
    float totaltime = (time_end.tv_sec - time_start.tv_sec)
                    + (time_end.tv_usec - time_start.tv_usec) / 1000000.0f;
                    
         
                    
    printf("\n\nProcess time %f seconds\n", totaltime);
    
    return 0;
}
