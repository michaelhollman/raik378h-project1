#include <string.h>
#include <stdio.h>

#include "int_node.c"

int main()
{
    int_node_t node;
    node.next = 2;
    node.previous = 3;
    node.fileType = 4;
    node.num_key_value_pairs = 4;

    node.keys = NULL;
    node.fileNumbers=NULL;
    node.keys = (int *)malloc(sizeof(int) *
                                               node.num_key_value_pairs);
    node.fileNumbers = (int *)malloc(sizeof(int) *
                                               node.num_key_value_pairs);
    int _keys[4] = {0, 1, 2, 3};
    node.keys = &_keys;
    int _fileNums[4] = {100, 200, 300, 400};
    node.fileNumbers = &_fileNums;

    //print_node(&node);
    printf("%d", 22);
    write_node(2, &node);

    //int_node_t *node2 = read_node(1);
    //print_node(node2);
    return 0;
}
