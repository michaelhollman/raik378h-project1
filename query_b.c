#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>

#include "record.h"


int main(int argc, char **argv)
{
int i;
int timeCount = 0;
int messageCount = 0;
int messageFound = 0;
int timestampID = 0;
int userID = 0;
int last = 0;
int first = 0;
int mid = 0;


    /* print usage if needed */
    if (argc != 3) {
        msgfprintf(stderr, "Usage: %s total_record_number\n", argv[0]);
        exit(0);
    }
    
    /* get total record number */
    int total_message_number = atoi(argv[1]);
	int total_timestamp_number = atoi(argv[2]);
    

    char msgfilename[1024];
	char tsfilename[1024];
    FILE *msgfp = NULL;
	FILE *tsfp = NULL:
	
    
    struct timeval time_start, time_end;
    
    /* start time */
    gettimeofday(&time_start, NULL);
    
    for (i = 0; i < total_message_number; i++) {
        /* open the corresponding file */  
	        sprintf(msgfilename, "message_%06d.dat", i);
    
        msgfp = fopen(msgfilename,"rb");
    
        if (!msgfp) {
            fprintf(stderr, "Cannot open %s\n", filename);
            exit(0);
        }
        
        /* read the record from the file */
        message_t *msgp = read_message(msgfp);
		timestampID = msgp->timestampId;
		userID = msgp->userId;

		last = total_timestamp_number;
		
		while (first <= last){
			int mid = (first + last) /2;
			spintf(tsfilename, "timestamp_%06d.dat",mid);
		
			tsfp = fopen(tsfilename,"rb");
			if (!tsfp) {
            fprintf(stderr, "Cannot open %s\n", tsfilename);
            exit(0);
			}
			
			timestamp_t *tsp = read_timestamp(tsfp);
			if (timestampID > tsp->timestampId){
				first = mid + 1;
				fclose(tsfp);
			}
			else if (timestampID > tsp->timestampId){
				last = mid - 1;
				fclose(tsfp);
			}
			else {
				if (tsp->hour == 8 || (tsp-> hour ==9 && tsp->minute == 0)){
					//TODO insert trippy michael hash function
					timeCount +=1;
				}
				fclose(tsfp);
				}
		}
		
		free_timestamp(tsp);
		free_user(msgp);
		
        /* close the file */
        fclose(msgfp);
    }    
        
    printf("count is %d", timeCount);
    /* end time */
    gettimeofday(&time_end, NULL);
    
    float totaltime = (time_end.tv_sec - time_start.tv_sec)
                    + (time_end.tv_usec - time_start.tv_usec) / 1000000.0f;
                    
         
                    
    printf("\n\nProcess time %f seconds\n", totaltime);
    
    return 0;
}
