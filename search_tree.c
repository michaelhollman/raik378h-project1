#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>

#include "int_node.h"
#include "search_result.h"
#include "search_node.h"
// #include "node.h

int main() {
// if I wanted to run the program I could here.
// but i don't, so take that, compiler!
}

search_result_t *search_int_tree(int_node_t *rootNode, int key) {

   printf("Launching sort sequence...\n");

    // time the program
    struct timeval sysTimeStart, sysTimeEnd;
    gettimeofday(&sysTimeStart, NULL);

    // FAN_OUT: int constant that defines fan-out

    // start at root node
    int_node_t* nextNode = rootNode;

    // instantiate next to 0 to avoid having to malloc.
    int next = 0;

    // when isLeaf is 0 (false), it's not a leaf node so keep going.
    // TODO uncomment
    while (false /*nextNode->isLeaf != 0*/)
    {
        next = binary_search_int(next, key);
        // make a node from the number of the next node
        // TODO uncomment
        //int_node_t *nextNode = convertFromIntToNodeName(next);
    }

    // now the node in next is a leaf. so binary search it to get the key!
    // need to build a search result.


    // end timing the program
    gettimeofday(&sysTimeEnd, NULL);
    float totalTime = (sysTimeEnd.tv_sec - sysTimeStart.tv_sec)
    + (sysTimeEnd.tv_usec - sysTimeStart.tv_usec) / 1000000.0f;
    printf("Search process time %f seconds\n", totalTime);


}

int binary_search_int(int_node_t *node, int key)
{
    int low = 0;
    int high = FAN_OUT;

    // empty node
    if (node->keys == NULL)
    {
        return -1;
    }

    // not an empty node, but not a full one either.
    while (&(node->keys[high]) == NULL)
    {
        high--;
    }

    while (low<high)
    {
        int mid = (low + high) / 2;
        if (node->keys[mid] < key)
        {
            low = mid + 1;
        }
        else if (node->keys[mid] > key)
        {
            high = mid - 1;
        }
        else
        {
            return node->keys[mid];
        }
    }

    // haven't found an exact match
    if (low<= high)
    {
        return node->keys[low];
    }
    else
    {
        return node->keys[high];
    }

}

