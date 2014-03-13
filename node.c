#include <stdio.h>
#include "node.h"

const char* const TABLE_TYPE[] = { "user", "state", "city", "message", "timestamp", "datestamp" };
const char* const NODE_TYPE[] = { "tree", "leaf" };

int filename_for_node(char* outchar, int tableType, int fileNumber)
{
    return sprintf(outchar, "bplus/%s_node_%08d.dat", TABLE_TYPE[tableType], fileNumber);
}