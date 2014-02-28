#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#include "record.h"
#include "user.h"
#include "message.h"
#include "location.h"
#include "timestamp.h"

int main(int argc, char **argv)
{
    int i;
<<<<<<< Updated upstream
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

=======
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
>>>>>>> Stashed changes
    /* print usage if needed */
    if (argc != 3) {
        fprintf(stderr, "Usage: %s total_user_number total_location_number\n", argv[0]);
        exit(0);
    }

    /* get total record number */
    int total_user_number = atoi(argv[1]);
    int total_location_number = atoi(argv[2]);


    char filename[1024];
    char locfilename[1024];
    FILE *fp = NULL;
    FILE *lf = NULL;

    struct timeval time_start, time_end;

    /* start time */
    gettimeofday(&time_start, NULL);

    for (i = 0; i < total_user_number; i++) {

        /* read the record from the file */
        //TODO Insert Casseys method to read the file
        user_t *up = read_user(i);

        /* =========== start of data processing code ================ */
        locationID = up-> locationId;
        last = total_location_number;

        while (first <= last){
            int mid = (first + last) /2;

            if (!lf) {
                fprintf(stderr, "Cannot open %s\n", locfilename);
                exit(0);
            }

            location_t *lp = read_location(mid);
            if (locationID > lp->locationId){
                first = mid + 1;
                fclose(lf);
            }
            else if (locationID < lp->locationId){
                last = mid - 1;
                fclose(lf);
            }
            else {
                if (strcmp(lp->state, nebraska) == 0){
                    nebraskaCount += 1;
                }
                fclose(lf);
                }
                free_location(lp);
            }

               free_user(up);
               fclose(fp);
        }

    printf("count is %d", nebraskaCount);
    /* end time */
    gettimeofday(&time_end, NULL);

    float totaltime = (time_end.tv_sec - time_start.tv_sec)
                    + (time_end.tv_usec - time_start.tv_usec) / 1000000.0f;



    printf("\n\nProcess time %f seconds\n", totaltime);

    return 0;
}
