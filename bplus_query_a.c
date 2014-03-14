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

    state_t *fakeState = (state_t *)malloc(sizeof(state_t));
    sprintf(fakeState->name, "Nebraska");


    unsigned long stateKey = hash_state(fakeState);
    free_state(fakeState);

    bplus_roots_t *roots = read_bplus_roots();
    int stateRoot = roots->state;
    printf("state root: %d", stateRoot);
    // find the leaf nodes that match Nebraska
    search_result_t *state_search_result = search_bplus(stateRoot, TABLE_TYPE_STATE, stateKey);


    if (state_search_result->count != 1) {
        printf("We found more than 1 Nebraska ID. This is problematic.");
        return 0;
    }

    search_result_node_t *state_search_node = state_search_result-> head;
    state_t *state = read_state(state_search_node->fileNumber);
    int nebraskaId = state->stateId;
    printf("\nFound %d states where name is %s and id is %d\n", state_search_result->count, state->name, state->stateId);

    int userRoot = roots->user;
    search_result_t *users_search_result = search_bplus(userRoot, TABLE_TYPE_USER, nebraskaId);

    printf("Found %d users from %s (state id %d)\n", users_search_result->count, "Nebraska", nebraskaId);

    // end timing the program
    gettimeofday(&sysTimeEnd, NULL);
    float totalTime = (sysTimeEnd.tv_sec - sysTimeStart.tv_sec)
    + (sysTimeEnd.tv_usec - sysTimeStart.tv_usec) / 1000000.0f;
    printf("Process time %f seconds\n", totalTime);

    return 0;
}
