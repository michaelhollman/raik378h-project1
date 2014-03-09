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

    int *_keys = {0, 1, 2, 3};
    node.keys = _keys;
    int *_fileNums = {100, 200, 300, 400};
    node.fileNumbers = _fileNums;

    print_node(&node);

    return 0;
}
