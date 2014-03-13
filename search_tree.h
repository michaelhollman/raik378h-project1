#ifndef _search_tree_h
#define _search_tree_h

search_result_t *search_int_tree(int_node_t *rootNode, int key);
void build_search_result(int_node_t *node, int key, int firstKeyIndex, search_result_t *searchResult);
int binary_search_int(int_node_t *node, int key);


#endif
