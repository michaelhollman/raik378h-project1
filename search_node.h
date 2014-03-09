#ifndef _search_node_h
#define _search_node_h

#include <stdio.h>
#include <stdlib.h>

// from top answer: http://stackoverflow.com/questions/7474774/typedef-a-struct-containing-a-pointer-to-same-type
typedef struct search_node_t search_node_t;

struct search_node_t {
    int fileNumber;
    search_node_t *next;
};

#endif
