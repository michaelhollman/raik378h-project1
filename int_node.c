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
    int i;
    for (i = 0; i < node->num_key_value_pairs; i++) {
        printf("\tKey: %08d", node->keys[i]);
        printf(", Value: %08d", node->fileNumbers[i]);
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
    node->fileNumbers = NULL;

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
        if (node->fileNumbers == NULL) {
            fprintf(stderr, "Cannot allocate memory for keys.\n");
            exit(0);
        }

    //read each key from file
        int i;
        for(i = 0; i < node->num_key_value_pairs; i++) {
            fread(&(node->keys[i]), sizeof(int), 1, fp);
        }

        // read each value (fileNumber) from file
        int j;
        for(j = 0; j < node->num_key_value_pairs; j++) {
            fread(&(node->fileNumbers[j]), sizeof(int), 1, fp);
        }

    return node;
    }
}

void write_node(int fileNum, int_node_t *node) {
    printf("%d", 0);
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

    printf("%d",1);
    //write each key from file
    int i;
    for(i = 0; i < node->num_key_value_pairs; i++) {
        fwrite(&(node->keys[i]), sizeof(int), 1, fp);
    }
    printf("%d", 2);
    // write each value (fileNumber) from file
    int j;
    for(j = 0; j < node->num_key_value_pairs; i++) {
        fwrite(&(node->fileNumbers[j]), sizeof(int), 1, fp);
    }

    fclose(fp);
}

void free_node(int_node_t *node)
{
    if(node==NULL) {
        return;
    }
    //if (node->num_key_value_pairs > 0) {
    //    free(node->keys);
    //    free(node->fileNumbers);
    //}
    free(node);
}

int compare_nodes(const void *a, const void *b)
{
    return (((int_node_t *)a)->keys[0] - ((int_node_t *)b)->keys[0]);
}