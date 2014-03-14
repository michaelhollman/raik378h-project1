#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>

#include "int_node.h"
#include "search_result.h"
#include "search_node.h"
#include "search_tree.h"
#include "state.h"

int main(int argc, char **argv)
{
    // time the program
    struct timeval sysTimeStart, sysTimeEnd;
    gettimeofday(&sysTimeStart, NULL);

    state_t *state = (state_t *)malloc(sizeof(state_t));
    sprintf(state->name, "Nebraska");


    unsigned long stateKey = hash_state(state);
    // printf("%lu\n", stateKey);

    b_plus_roots_t *roots = read_bplus_roots();
    int stateRoot = roots->state;

    int_node_t *rootNode = read_node(stateRoot, TABLE_TYPE_STATE);

    search_result_t *search_int_tree(int_node_t *rootNode, int key, int tableType) {

    return 0;
}
