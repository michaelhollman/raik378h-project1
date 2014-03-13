#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>

#include "int_node.h"

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

const char* const TABLE_TYPE[] = { "user", "state", "city", "message", "timestamp", "datestamp" };
const char* const NODE_TYPE[] = { "tree", "leaf" };

int filename_for_node(char* outchar, int tableType, int fileNumber)
{
    return sprintf(outchar, "bplus/%s_node_%08d.dat", TABLE_TYPE[tableType], fileNumber);
}

void print_node(int_node_t *node)
{
    // node cannot be NULL
    if (node == NULL) {
        fprintf(stderr, "The node is NULL\n");
        exit(0);
    }

    // print node
    printf("Node:\n");
    printf("\t%-12s: %d\n", "table type", node->tableType);
    printf("\t%-12s: %d\n", "node type", node->nodeType);
    printf("\t%-12s: %08d\n", "previous", node->previous);
    printf("\t%-12s: %08d\n", "next", node->next);
    printf("\t%-12s: %08d\n", "first file", node->firstFile);
    printf("\t%-12s: %08d\n", "count", node->count);
    int i;
    for (i = 0; i < node->count; i++) {
        printf("\t\t%-12s: %08d | %08d\n", "key | file", node->keys[i], node->files[i]);
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
    
    fclose(fp);
    
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

// assume that the roots will be manually created as abc_xyz_0000000.dat
static int nodeFileCounter[] = {0, 0, 0, 0, 0, 0};

int insert_node(int rootFileNum, int tableType, int newKeyToInsert, int newFileNumToInsert)
{
    insert_node_result_t result;
    result.didSplit = false;
    
    insert_node_internal(&result, rootFileNum, tableType, newKeyToInsert, newFileNumToInsert);

    if (result.didSplit)
    {
        int_node_t newRoot;
        int newRootFileNum = ++nodeFileCounter[tableType];

        newRoot.next = -1;
        newRoot.previous = -1;
        newRoot.tableType = tableType;
        newRoot.nodeType = NODE_TYPE_TREE;
        newRoot.count = 1;
        newRoot.firstFile = rootFileNum;
        newRoot.keys[0] = result.newKey;
        newRoot.files[0] = result.newFile;

        write_node(newRootFileNum, &newRoot);
        return newRootFileNum;
    }
    else
    {
        // didn't split. root stays the same
        return rootFileNum;
    }

    return 0;
}

void insert_node_internal(insert_node_result_t *result, int nodeFileNum, int tableType, int newKeyToInsert, int newFileNumToInsert)
{
    int i, j;
    // open this current node
    int_node_t *node = read_node(nodeFileNum, tableType);

    // LEAF NODE
    if (node->nodeType == NODE_TYPE_LEAF)
    {
        // we're going to be directly inserting or splitting
        if (node->count >= FAN_OUT)
        {
            // create new leaf node
            int_node_t newNode;
            int newNodeFileNum = ++nodeFileCounter[tableType];

            newNode.next = node->next;
            newNode.previous = nodeFileNum;
            node->next = newNodeFileNum;

            newNode.tableType = tableType;
            newNode.nodeType = NODE_TYPE_LEAF;
            newNode.firstFile = -1;

            // create temp arrays to split this node into two
            int tempArraySize = node->count + 1;
            int tempKeys[tempArraySize];
            int tempFiles[tempArraySize];
            bool insertedNew = false;

            for (i = 0; i < tempArraySize; i++)
            {
                if (i < node->count && node->keys[i] <= newKeyToInsert)
                {
                    tempKeys[i] = node->keys[i];
                    tempFiles[i] = node->files[i];
                }
                else if (!insertedNew)
                {
                    tempKeys[i] = newKeyToInsert;
                    tempFiles[i] = newFileNumToInsert;
                    insertedNew = true;
                }
                else
                {
                    tempKeys[i] = node->keys[i-1];
                    tempFiles[i] = node->files[i-1];
                }
            }

            int mid = tempArraySize / 2;
            node->count = mid;
            newNode.count = tempArraySize - mid;

            // set old node values
            for (i = 0; i < FAN_OUT; i++)
            {
                if (i < node->count)
                {
                    node->keys[i] = tempKeys[i];
                    node->files[i] = tempFiles[i];
                }
                else
                {
                    node->keys[i] = 0;
                    node->files[i] = 0;
                }
            }

            // set new node values
            for (i = 0; i < FAN_OUT; i++)
            {
                if (i < newNode.count)
                {
                    newNode.keys[i] = tempKeys[i+mid];
                    newNode.files[i] = tempFiles[i+mid];
                }
                else
                {
                    newNode.keys[i] = 0;
                    newNode.files[i] = 0;
                }
            }

            // write both nodes
            write_node(nodeFileNum, node);
            write_node(newNodeFileNum, &newNode);

            // modify result
            result->didSplit = true;
            result->newKey = newNode.keys[0];
            result->newFile = newNodeFileNum;
        }
        else
        {
            // insert into this leaf node, mark result as such
            i = 0;
            while(i < node->count && newKeyToInsert >= node->keys[i])
            {
                i++;
            }
            for (j = FAN_OUT - 1; j > i; j--)
            {
                node->keys[j] = node->keys[j-1];
                node->files[j] = node->files[j-1];
            }
            node->keys[i] = newKeyToInsert;
            node->files[i] = newFileNumToInsert;
            node->count++;

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
        if (newKeyToInsert < node->keys[0])
        {
            //recurse into the first child
            insert_node_internal(result, node->firstFile, tableType, newKeyToInsert, newFileNumToInsert);
        }
        else
        {
            // binary search keys on node
            int first = 0, last = node->count - 1, mid, found = -1;
            while (first <= last && found == -1)
            {
                mid = (first + last) / 2;
                int comparison = newKeyToInsert - node->keys[mid];

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
            insert_node_internal(result, found, tableType, newKeyToInsert, newFileNumToInsert);
        }

        if (result->didSplit)
        {
            // add new key/file
            if (node->count >= FAN_OUT)
            {
                // split and create new tree node
                int_node_t newNode;
                int newNodeFileNum = ++nodeFileCounter[tableType];

                newNode.next = node->next;
                newNode.previous = nodeFileNum;
                node->next = newNodeFileNum;

                newNode.tableType = tableType;
                newNode.nodeType = NODE_TYPE_TREE;
                newNode.firstFile = -1; // change this later

                // create temp arrays to split this node into two
                int tempArraySize = node->count + 1;
                int tempKeys[tempArraySize];
                int tempFiles[tempArraySize];
                bool insertedNew = false;
                for (i = 0; i < node->count; i++)
                {
                    if (node->keys[i] <= result->newKey)
                    {
                        tempKeys[i] = node->keys[i];
                        tempFiles[i] = node->files[i];
                    }
                    else if (!insertedNew)
                    {
                        tempKeys[i] = result->newKey;
                        tempFiles[i] = result->newFile;
                        insertedNew = true;
                        i--;
                    }
                    else
                    {
                        tempKeys[i+1] = node->keys[i];
                        tempFiles[i+1] = node->files[i];
                    }
                }

                int mid = tempArraySize / 2;
                node->count = mid;
                newNode.count = tempArraySize - mid - 1;

                // rewrite old node values
                for (i = 0; i < FAN_OUT; i++)
                {
                    if (i < node->count)
                    {
                        node->keys[i] = tempKeys[i];
                        node->files[i] = tempFiles[i];
                    }
                    else
                    {
                        node->keys[i] = 0;
                        node->files[i] = 0;
                    }
                }

                // write new node values
                for (i = 0; i < FAN_OUT; i++)
                {
                    if (i < newNode.count)
                    {
                        newNode.keys[i] = tempKeys[mid + 1];
                        newNode.files[i] = tempFiles[mid + 1];
                    }
                    else
                    {
                        newNode.keys[i] = 0;
                        newNode.files[i] = 0;
                    }
                }
                newNode.firstFile = tempFiles[mid];

                // write both nodes
                write_node(nodeFileNum, node);
                write_node(newNodeFileNum, &newNode);

                // mid gets moved up to the next layer
                result->didSplit = true;
                result->newKey = tempKeys[mid];
                result->newFile = newNodeFileNum;
            }
            else
            {
                i = 0;
                while(i < node->count && result->newKey >= node->keys[i])
                {
                    i++;
                }
                for (j = FAN_OUT - 1; j > i; j--)
                {
                    node->keys[j] = node->keys[j-1];
                    node->files[j] = node->files[j-1];
                }
                node->keys[i] = result->newKey;
                node->files[i] = result->newFile;
                node->count++;

                // re-write node
                write_node(nodeFileNum, node);

                // modify result
                result->didSplit = false;
                result->newKey = -1;
                result->newFile = -1;
            }
        }
        // else, do nothing
    }
    free_node(node);
}

