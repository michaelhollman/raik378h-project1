#ifndef _search_result_h
#define _search_result_h


#include <stdio.h>
#include <stdlib.h>

#include "search_node.h"
#define TEXT_SHORT      64
#define TEXT_LONG       1024

typedef struct {
    int count;
    search_node_t *head;
} search_result_t;


#endif
