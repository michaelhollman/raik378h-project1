#ifndef _node_h
#define _node_h

// Change this value to adjust the fan-out of the tables
#define FAN_OUT         5

#define TEXT_SHORT      64
#define TEXT_LONG       1024

#define TABLE_TYPE_USER         0
#define TABLE_TYPE_STATE        1
#define TABLE_TYPE_CITY         2
#define TABLE_TYPE_MESSAGE      3
#define TABLE_TYPE_TIMESTAMP    4
#define TABLE_TYPE_DATESTAMP    5

#define NODE_TYPE_TREE          0
#define NODE_TYPE_LEAF          1

int filename_for_node(char* outchar, int tableType, int fileNumber);

#endif
