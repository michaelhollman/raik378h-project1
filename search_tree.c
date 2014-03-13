#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>

#include "int_node.h"
#include "search_result.h"
#include "search_node.h"
#include "search_tree.h"
#include "node.h"

int main() {
// if I wanted to run the program I could here.
// but i don't, so take that, compiler!
}

search_result_t *search_int_tree(int_node_t *rootNode, int key, int tableType) {

   printf("Launching sort sequence...\n");

    // time the program
    struct timeval sysTimeStart, sysTimeEnd;
    gettimeofday(&sysTimeStart, NULL);

    // FAN_OUT: int constant that defines fan-out

    // start at root node
    int_node_t* nextNode = rootNode;

    // instantiate next to 0 to avoid having to malloc.
    int next = 0;

    while (nextNode->nodeType == NODE_TYPE_TREE)
    {
        next = binary_search_int(nextNode, key);
        // make a node from the number of the next node
        // TODO: convertFromIntToNodeName doesn't do anything right now - needs implemented from how Michael fixed it
        int_node_t *nextNode = read_node(next, tableType);
    }

    // now the node in next is a leaf. so binary search it to get the key!
    // need to  build a search result.

    // binary search NextNode to find first instance of key.
    // since this is not a leaf node, the keys should go to data files, not more nodes.
    int firstKeyIndex = binary_search_int(nextNode, key);
    search_result_t searchResult;

    if (nextNode->keys[firstKeyIndex] != key)
    {
    // this could be false since our binary search function is set up to get the closest match if it can't find the exact key
    // ie, instead of returning -1 when we search 5 and it isn't there, we'll return the next closest number
            searchResult.head = NULL;
            searchResult.count = 0;
    }
    else {
        // hooray, we found one!
        int searchResultCount = 1;
        search_node_t searchHead;
        searchHead.fileNumber = nextNode->files[firstKeyIndex];
        searchHead.next = NULL;
        searchResult.head = &searchHead;

        build_search_result(nextNode, key, firstKeyIndex, &searchResult);


    }

    // end timing the program
    gettimeofday(&sysTimeEnd, NULL);
    float totalTime = (sysTimeEnd.tv_sec - sysTimeStart.tv_sec)
    + (sysTimeEnd.tv_usec - sysTimeStart.tv_usec) / 1000000.0f;
    printf("Search process time %f seconds\n", totalTime);


}

void build_search_result(int_node_t *node, int key, int firstKeyIndex, search_result_t *searchResult)
{
    // search backward from the key you found w/ binary search
        int i = firstKeyIndex - 1;
        int tableType = node->tableType;
        while (i > 0 && node->keys[i] == key)
        {
            search_node_t newSearchHead;
            newSearchHead.fileNumber = node->files[i];
            newSearchHead.next = searchResult->head;
            searchResult->head = &newSearchHead;
            searchResult->count++;
            i--;
        }
        if (i == 0)
        {
            //need to check the previous node starting at last key if i = 0 is a match
            int next = node->next;
            int_node_t *nextNode = read_node(next, tableType);
            int beginIndex = nextNode->count - 1;
            build_search_result(nextNode, key, beginIndex, searchResult);
        }

        // now search forwards from first key
        i = firstKeyIndex + 1;

        int num_keys = node->count;
        while ((i< num_keys - 1) && node->keys[i] == key) {
            search_node_t newSearchHead;
            newSearchHead.fileNumber = node->files[i];
            newSearchHead.next = searchResult->head;
            searchResult->head = &newSearchHead;
            searchResult->count++;
        }
        if (i == num_keys - 1)
        {
            // need to check the next node starting at the first key if i=0 is a match
            int next = node->next;
            int_node_t *nextNode = read_node(next, tableType);
            build_search_result(nextNode, key, 0, searchResult);
        }

}

int binary_search_int(int_node_t *node, int key)
{
    int low = 0;
    int high = node->count -1;

    // empty node
    if (node->keys == NULL)
    {
        return -1;
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

