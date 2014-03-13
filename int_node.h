#ifndef _int_node_h
#define _int_node_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "node.h"

#define TEXT_SHORT      64
#define TEXT_LONG       1024

// int - based node
typedef struct {
    int next;                   // pointer to next adjacent node
    int previous;               // pointer to prev adjacent node
    int tableType;              // "enum" value of type of object in this node
    int nodeType;               // "enum" value of type of node (leaf vs tree)
    int count;                  // the number of filled "cells"
    int firstFile;              // extra first file pointer for tree nodes
    int keys[FAN_OUT];          // array of keys (the value of what the table is sorted by)
    int files[FAN_OUT];         // file number for the corresponding key
} int_node_t;

typedef struct {
    bool didSplit;
    int newKey;
    int newFile;
} insert_node_result_t;

void print_node(int_node_t *node);

int_node_t *read_node(int fileNum, int tableType);

void write_node(int fileNum, int_node_t *node);

void free_node(int_node_t *node);

int compare_nodes(const void *a, const void *b);

// returns root file num
int insert_node(int rootFileNum, int tableType, int insertNewKey, int newFileNumToInsert);

void insert_node_internal(insert_node_result_t *result, int nodeFileNum, int tableType, int newKey, int newFileNumToInsert);


#endif
