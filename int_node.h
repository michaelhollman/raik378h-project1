#ifndef _int_node_h
#define _int_node_h

#include <stdio.h>
#include <stdlib.h>

#define TEXT_SHORT      64
#define TEXT_LONG       1024
#define FAN_OUT         200
// int - based node
typedef struct {
    int next;
    int previous;
    int fileType;
    int num_key_value_pairs;
    int *keys;
    int *fileNumbers;
    int isLeaf;
} int_node_t;

void print_node(int_node_t *node);

int_node_t *read_node(int fileNum);

void write_node(int fileNum, int_node_t *node);

void free_node(int_node_t *node);

int compare_nodes(const void *a, const void *b);

int_node_t *convertFromIntToNode(int fileNumber);

#endif
