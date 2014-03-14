#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>

#include "int_node.h"
#include "state.h"
#include "bplus_roots.h"

int main(int argc, char **argv)
{
    // time the program
    struct timeval sysTimeStart, sysTimeEnd;
    gettimeofday(&sysTimeStart, NULL);
    
    // get the necessary b+ roots
    bplus_roots_t *roots = read_bplus_roots();
    int stateRoot = roots->state;
    int userRoot = roots->user;
    free_bplus_roots(roots);
    
    // get the hash for "Nebraska"
    state_t *fakeState = (state_t *)malloc(sizeof(state_t));
    sprintf(fakeState->name, "Nebraska");
    int stateKey = (int) hash_state(fakeState);
    free_state(fakeState);
    
    // query state b+ tree for nebraska state
    search_result_t *stateSearchResult = search_bplus(stateRoot, TABLE_TYPE_STATE, stateKey);
    
    if (stateSearchResult->count != 1)
    {
        printf("WARNING: We found !1 states matching Nebraska. This is problematic.\n");
    }
    
    // get Nebraska's stateId
    state_t *state = read_state(stateSearchResult->head->fileNumber);
    int nebraskaId = state->stateId;
    
    // get users with matching state id
    search_result_t *userSearchResult = search_bplus(userRoot, TABLE_TYPE_USER, nebraskaId);
    
    printf("Found %d users from %s (state id %d)\n", userSearchResult->count, "Nebraska", nebraskaId);
    
    free_state(state);
    free_search_result(stateSearchResult);
    free_search_result(userSearchResult);
    
    // end timing the program
    gettimeofday(&sysTimeEnd, NULL);
    float totalTime = (sysTimeEnd.tv_sec - sysTimeStart.tv_sec)
    + (sysTimeEnd.tv_usec - sysTimeStart.tv_usec) / 1000000.0f;
    printf("Process time %f seconds\n", totalTime);
    
    return 0;
}
