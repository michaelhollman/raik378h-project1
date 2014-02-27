#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>

#include "record.h"

int main(int argc, char **argv)
{
    /* print usage if needed */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s record_number\n", argv[0]);
        exit(0);
    }
    
    /* get record number */
    int record_number = atoi(argv[1]);
    
    
    /* open the corresponding file */
    char filename[1024];
    sprintf(filename, "record_%06d.dat", record_number);
    
    FILE *fp = fopen(filename,"rb");
    
    if (!fp) {
        fprintf(stderr, "Cannot open %s\n", filename);
        exit(0);
    }
    
    struct timeval time_start, time_end;
    
    /* start time */
    gettimeofday(&time_start, NULL);
    
    /* read the record from the file */
    record_t *rp = read_record(fp);
    
    /* print the record */
    print_record(rp);
    
    /* free memory */
    free_record(rp);
    
    /* close the file */
    fclose(fp);
    
    /* end time */
    gettimeofday(&time_end, NULL);
    
    float totaltime = (time_end.tv_sec - time_start.tv_sec)
                    + (time_end.tv_usec - time_start.tv_usec) / 1000000.0f;
                    
         
                    
    printf("\n\nProcess time %f seconds\n", totaltime);
    
    return 0;
}
