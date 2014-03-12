#include <string.h>
#include <stdio.h>

#include "int_node.h"
#include "node.h"

int main()
{
    int_node_t node;
    
    node.next = 2;
    node.previous = 3;
    node.tableType = TABLE_TYPE_USER;
    node.nodeType = NODE_TYPE_TREE;
    node.count = 4;
    node.firstFile = -1;
    
    node.keys[0] = 99;
    node.keys[1] = 98;
    node.keys[2] = 97;
    node.keys[3] = 96;

    node.files[0] = 89;
    node.files[1] = 88;
    node.files[2] = 87;
    node.files[3] = 86;
    
    


    print_node(&node);
    
    write_node(2, &node);

    int_node_t *node2 = read_node(2, TABLE_TYPE_USER);
    
    print_node(node2);
    
    return 0;
}
