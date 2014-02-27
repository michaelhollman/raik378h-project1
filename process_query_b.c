#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>

#include "record.h"


int main(int argc, char **argv)
{
    int i;
int j;
j = 0;
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
        fprintf(stderr, "Usage: %s total_record_number\n", argv[0]);
        exit(0);
    }
    
    /* get total record number */
    int total_message_number = atoi(argv[1]);
	int total_timestamp_number = atoi(argv[2]);
    

    char filename[1024];
	char tsfilename[1024];
    FILE *fp = NULL;
	FILE *ts = NULL:
	
    
    struct timeval time_start, time_end;
    
    /* start time */
    gettimeofday(&time_start, NULL);
    
    for (i = 0; i < total_message_number; i++) {
        /* open the corresponding file */  
	        sprintf(filename, "message_%06d.dat", i);
    
        fp = fopen(filename,"rb");
    
        if (!fp) {
            fprintf(stderr, "Cannot open %s\n", filename);
            exit(0);
        }
        
        /* read the record from the file */
		//Cassey's read method
        record_t *rp = read_record(fp);
		timestampID = rp->timestampId;
		userID = rp->userId;
	    		
        /* =========== start of data processing code ================ */
		last = total_timestamp_number;
		
		while (first <= last){
			int mid = (first + last) /2;
			spintf(tsfilename, "timestamp_%06d.dat",mid);
		
			ts = fopen(tsfilename,"rb");
			if (!ts) {
            fprintf(stderr, "Cannot open %s\n", tsfilename);
            exit(0);
			}
			if (timestampID > ts->timestampId){
				first = mid + 1;
				fclose(ts);
			}
			else if (timestampID > ts->timestampId){
				last = mid - 1;
				fclose(ts);
			}
			else {
				if (ts->hour == 8 || (ts-> hour ==9 && ts->minute == 0)){
					//TODO insert trippy michael hash function
					timeCount +=1;
				}
				fclose(ts);
				}
		}
		

	    //print_record(rp);
        
        /* =========== end of data processing code ================ */    
    
        /* free memory */
        free_record(rp);
    
        /* close the file */
        fclose(fp);
    }    
        
    printf("count is %d", timeCount);
    /* end time */
    gettimeofday(&time_end, NULL);
    
    float totaltime = (time_end.tv_sec - time_start.tv_sec)
                    + (time_end.tv_usec - time_start.tv_usec) / 1000000.0f;
                    
         
                    
    printf("\n\nProcess time %f seconds\n", totaltime);
    
    return 0;
}
