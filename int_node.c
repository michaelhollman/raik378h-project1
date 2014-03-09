#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "int_node.h"

// typedef struct {
//    int next;
//    int previous;
//    int key;
//    int fileNumber;
//    int fileType;
// } int_node_t;

void print_node(int_node_t *node)
{
    // node cannot be NULL
    if (node == NULL) {
        fprintf(stderr, "The node is NULL\n");
        exit(0);
    }

    // print node
    printf("\tfileType: %08d\n", node->fileType);
    printf("\tnext: %08d\n", node->next);
    printf("\tprevious: %08d\n", node->previous);
    //print keys if the key/value number is greater than 0
    for (i = 0; i < node->num_key_value_pairs; i++) {
        printf("\tNode Key: ", node->keys[i]);
        printf(", Node Value: ", node->fileNumbers[i]);
    }
}

int_node_t *read_node(int fileNum)
{
    // set up file
    FILE *fp;
    char filename[1024];
    sprintf(filename, "node_%08d.dat", fileNum);

    // open file
    fp = fopen(filename, "rb");

    if (!fp) {
        fprintf(stderr, "Cannot open %s\n", filename);
        exit(0);
    }

    // allocate memory for the record
    int_node_t *node = (int_node_t *)malloc(sizeof(int_node_t));

    // memory error
    if (node== NULL) {
        fprintf(stderr, "Cannot allocate memory for node.\n");
        exit(0);
    }

    // read node
    fread(&(node->next), sizeof(int), 1, fp);
    fread(&(node->previous), sizeof(int), 1, fp);
    fread(&(node->fileType), sizeof(int), 1, fp);
    fread(&(node->num_key_value_pairs), sizeof(int), 1, fp);

        //initalize keys & values
    node->keys = NULL;
    node->values = NULL

    //allocate memory for keys and values if the key/value number is greater than 0
    if (node->num_key_value_pairs > 0) {

        //allocate memory
        node->keys = (int *)malloc(sizeof(int) *
                                               node->num_key_value_pairs);
        node->fileNumbers = (int *)malloc(sizeof(int) *
                                               node->num_key_value_pairs);

        //memory error
        if (node->keys == NULL) {
            fprintf(stderr, "Cannot allocate memory for keys.\n");
            exit(0);
        }

        // another memory error
        if (node->values == NULL) {
            fprintf(stderr, "Cannot allocate memory for keys.\n");
            exit(0);
        }

    //read each key from file
        for(i = 0; i < node->num_key_value_pairs; i++) {
            fread(&(node->keys[i]), sizeof(int), 1, fp);
        }

        // read each value (fileNumber) from file
        for(i = 0; i < node->num_key_value_pairs; i++) {
            fread(&(node->fileNumbers[i]), sizeof(int), 1, fp);
        }

    return node;
}

void write_node(int fileNum, int_node_t *node) {
    // set up file
    FILE *fp;
    char filename[1024];
    sprintf(filename, "int_node_%08d.dat", fileNum);

    // open file
    fp = fopen(filename, "wb");
    if (!fp)
    {
        printf("Unable to open file.");
        return;
    }
    // write node
    fwrite(&(node->next), sizeof(int), 1, fp);
    fwrite(&(node->previous), sizeof(int), 1, fp);
    fwrite(&(node->fileType), sizeof(int), 1, fp);
    fwrite(&(node->num_key_value_pairs), sizeof(int), 1, fp);


    //write each key from file
    for(i = 0; i < node->num_key_value_pairs; i++) {
        fwrite(&(node->keys[i]), sizeof(int), 1, fp);
    }

    // write each value (fileNumber) from file
    for(i = 0; i < node->num_key_value_pairs; i++) {
        fwrite(&(node->fileNumbers[i]), sizeof(int), 1, fp);
    }

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
    return (((int_node_t *)a)->key - ((int_node_t *)b)->key);
}
