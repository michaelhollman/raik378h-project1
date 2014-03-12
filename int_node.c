#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "int_node.h"
#include "node.h"

// int - based node
//typedef struct {
//    int next;                   // pointer to next adjacent node
//    int previous;               // pointer to prev adjacent node
//    int tableType;              // "enum" value of type of object in this node
//    int nodeType;               // "enum" value of type of node (leaf vs tree)
//    int count;                  // the number of filled "cells"
//    int firstFile;              // extra first file pointer for tree nodes
//    int keys[FAN_OUT];          // array of keys (the value of what the table is sorted by)
//    int files[FAN_OUT];         // file number for the corresponding key
//} int_node_t;

void print_node(int_node_t *node)
{
    // node cannot be NULL
    if (node == NULL) {
        fprintf(stderr, "The node is NULL\n");
        exit(0);
    }
    
    // print node
    printf("\tfileType: %08d\n", node->nodeType);
    printf("\tnext: %08d\n", node->next);
    printf("\tprevious: %08d\n", node->previous);
    //print keys if the key/value number is greater than 0
    int i;
    for (i = 0; i < node->count; i++) {
        printf("\tKey: %08d", node->keys[i]);
        printf("  File#: %08d\n", node->files[i]);
    }
}

int_node_t *read_node(int fileNum, int tableType)
{
    // set up file
    FILE *fp;
    char filename[1024];
    
    filename_for_node(filename, tableType, fileNum);
    
    // open file
    fp = fopen(filename, "rb");
    
    if (!fp) {
        fprintf(stderr, "Cannot open %s\n", filename);
        exit(0);
    }
    
    // allocate memory for the record
    int_node_t *node = (int_node_t *)malloc(sizeof(int_node_t));
    
    // memory error
    if (node == NULL) {
        fprintf(stderr, "Cannot allocate memory for node.\n");
        exit(0);
    }
    
    // read node
    fread(&(node->next),        sizeof(int), 1, fp);
    fread(&(node->previous),    sizeof(int), 1, fp);
    fread(&(node->tableType),   sizeof(int), 1, fp);
    fread(&(node->nodeType),    sizeof(int), 1, fp);
    fread(&(node->count),       sizeof(int), 1, fp);
    fread(&(node->firstFile),   sizeof(int), 1, fp);
    fread(&(node->keys),        sizeof(int), FAN_OUT, fp);
    fread(&(node->files),       sizeof(int), FAN_OUT, fp);
    
    return node;
}


void write_node(int fileNum, int_node_t *node) {
    // set up file
    mkdir("bplus", 0777);
    FILE *fp;
    char filename[1024];
    filename_for_node(filename, node->tableType, fileNum);
    
    // open file
    fp = fopen(filename, "wb");
    if (!fp)
    {
        printf("Unable to open file.");
        return;
    }
    // write node
    fwrite(&(node->next),        sizeof(int), 1, fp);
    fwrite(&(node->previous),    sizeof(int), 1, fp);
    fwrite(&(node->tableType),   sizeof(int), 1, fp);
    fwrite(&(node->nodeType),    sizeof(int), 1, fp);
    fwrite(&(node->count),       sizeof(int), 1, fp);
    fwrite(&(node->firstFile),   sizeof(int), 1, fp);
    fwrite(&(node->keys),        sizeof(int), FAN_OUT, fp);
    fwrite(&(node->files),       sizeof(int), FAN_OUT, fp);
    
    fclose(fp);
}

void free_node(int_node_t *node)
{
    if(node==NULL) {
        return;
    }
    
    free(node);
}

int compare_nodes(const void *a, const void *b)
{
    return (((int_node_t *)a)->keys[0] - ((int_node_t *)b)->keys[0]);
}


// assume that the roots will be manually created as x_y_0000000.dat
static int nodeFileCounter[] = {0, 0, 0, 0, 0, 0};

int insert_node(int rootFileNum, int tableType, int key, int tableFileNum)
{
    int_node_t *root = read_node(rootFileNum, tableType);
    
    if (root->nodeType == NODE_TYPE_LEAF)
    {
        if (root->count > FAN_OUT)
        {
            // special case. root was a leaf node, is going to become a tree node
            // split root, create new root, holy cow
        }
        else
        {
            // insert into root (which is a leaf right now)
        }
    }
    else // NODE_TYPE_TREE
    {
        // get the leaf node we want to insert into
        int_node_t *leaf = find_leaf(rootFileNum, tableType, key);
        // insert into this leaf node.
    }
    
}

void insert_node_private(insert_node_result_t *result, int nodeFileNum, int tableType, int key, int tableFileNum)
{
    // open this current node
    int_node_t *node = read_node(nodeFileNum, tableType);
    // TODO free me later!
    
    // LEAF NODE
    if (node->nodeType == NODE_TYPE_LEAF)
    {
        // we're going to be directly inserting or splitting
        if (node->count >= FAN_OUT)
        {
            // create new leaf node
            int_node_t newNode;
            int newFileNum = ++nodeFileCounter[tableType];
            
            newNode.next = node->next;
            newNode.previous = nodeFileNum;
            node->next = newFileNum;
            
            newNode.tableType = tableType;
            newNode.nodeType = NODE_TYPE_LEAF;
            newNode.firstFile = -1;
            
            int half = node->count / 2;
            
            newNode.count = half;
            node->count = node->count - half;
            
            // split current node's keys and files
            for (int i = 0; i < half; i++)
            {
                newNode.keys[i] = node->keys[i+half];
                newNode.files[i] = node->files[i+half];
                node->keys[i+half] = 0;
                node->files[i+half] = 0;
            }
            
            // insert new key
            if (key < newNode.keys[0])
            {
                // into old node
                int i = 0, j;
                while(i < node->count && key >= node->keys[i])
                    i++;
                for (j = FAN_OUT - 1; j > i; j--)
                {
                    node->keys[j] = node->keys[j-1];
                    node->files[j] = node->files[j-1];
                }
                node->keys[i] = key;
                node->files[i] = newFileNum;
            }
            else
            {
                // into new node
                int i = 0, j;
                while(i < newNode.count && key >= newNode.keys[i])
                {
                    i++;
                }
                for (j = FAN_OUT - 1; j > i; j--)
                {
                    newNode.keys[j] = newNode.keys[j-1];
                    newNode.files[j] = newNode.files[j-1];
                }
                newNode.keys[i] = key;
                newNode.files[i] = newFileNum;
            }
            
            // write both nodes
            write_node(nodeFileNum, node);
            write_node(newFileNum, &newNode);
            
            // modify result
            result->didSplit = true;
            result->newKey = newNode.keys[0];
            result->newFile = newFileNum;
        }
        else
        {
            // insert into this leaf node, mark result as such
            int i = 0, j;
            while(i < node->count && key >= node->keys[i])
            {
                i++;
            }
            for (j = FAN_OUT - 1; j > i; j--)
            {
                node->keys[j] = node->keys[j-1];
                node->files[j] = node->files[j-1];
            }
            node->keys[i] = key;
            node->files[i] = newFileNum;
            
            // re-write node
            write_node(nodeFileNum, node);
            
            // modify result
            result->didSplit = false;
            result->newKey = -1;
            result->newFile = -1;
            
        }
    }
    // TREE NODE
    else
    {
        // find the appropriate child node, recurse deeper
        if (key < node->keys[0])
        {
            //recurse into the first child
            insert_node_private(result, node->firstFile, tableType, key, tableFileNum)
        }
        else
        {
            // binary search keys on node
            int first = 0, last = node->count - 1, mid, found = -1;
            while (first <= last && found == -1)
            {
                mid = (first + last) / 2;
                int comparison = key - node->keys[mid];
                
                if (comparison == 0)
                {
                    found = node->files[mid];
                }
                else if (comparison > 0)
                {
                    first = mid + 1;
                }
                else // comparison < 0
                {
                    last = mid - 1;
                }
            }
            // at this point, `last` will be moved to correspond with the key that points to the correct file.... I think. hopefully.
            found = (found == -1) ? node->files[last] : found;
            
            // insert into appropriate child
            insert_node_private(result, found, tableType, key, tableFileNum);
        }
        
        //check result for split, add key/file to current node, mark result
        
        // note: handle if this is the first insert (root)????
        
        // TODO
    }
}
