#include <string.h>
#include <stdio.h>

#include "int_node.h"
#include "node.h"
#include "record.h"
#include "user.h"
#include "message.h"
#include "city.h"
#include "state.h"
#include "timestamp.h"
#include "datestamp.h"
#include "file_count.h"

int main()
{
//    int_node_t node;
//    
//    node.next = 2;
//    node.previous = 3;
//    node.tableType = TABLE_TYPE_USER;
//    node.nodeType = NODE_TYPE_TREE;
//    node.count = 4;
//    node.firstFile = -1;
//    
//    node.keys[0] = 99;
//    node.keys[1] = 98;
//    node.keys[2] = 97;
//    node.keys[3] = 96;
//
//    node.files[0] = 89;
//    node.files[1] = 88;
//    node.files[2] = 87;
//    node.files[3] = 86;
//    
//    
//
//
//    print_node(&node);
//    
//    write_node(2, &node);
//
//    int_node_t *node2 = read_node(2, TABLE_TYPE_USER);
//    
//    print_node(node2);
    
    
    // example of filename_for_node
    
    char filename[TEXT_SHORT];
    filename_for_node(filename, TABLE_TYPE_TIMESTAMP, 23789);
    printf("%s\n", filename);
    
    
    
    // create root
//    int_node_t root;
//
//    root.next = -1;
//    root.previous = -1;
//    root.tableType = TABLE_TYPE_USER;
//    root.nodeType = NODE_TYPE_LEAF;
//    root.count = 0;
//    root.firstFile = -1;
//    
//    write_node(0, &root);
//    
//    int rootFileNum = 0;
//    
//    // insert multiples of 3
//    for (int i = 1; i <= 10; i++)
//    {
//        rootFileNum = insert_node(rootFileNum, TABLE_TYPE_USER, i*3, i*4);
//    }
//    
//    // insert multiples of 7
//    for (int i = 1; i <= 10; i++)
//    {
//        rootFileNum = insert_node(rootFileNum, TABLE_TYPE_USER, i*7, i*8);
//    }
//    
//   
//    printf("ROOT:  %d\n", rootFileNum);
//    int_node_t *rootRead = read_node(rootFileNum, TABLE_TYPE_USER);
//    print_node(rootRead);
//    free_node(rootRead);
//
//
//    for (int i = 0; i < 40; i++)
//    {
//        int_node_t *node = read_node(i, TABLE_TYPE_USER);
//        printf("FILE: %d\n",i);
//        print_node(node);
//        free_node(node);
//    }
    
    
    for (int i = 0; i < 50; i++){
        message_t *msg = read_message(i);
        print_message(msg);
        free_message(msg);
    }
    
    
    return 0;
}
