#include <string.h>
#include <stdio.h>

#include "int_node.h"
#include "bplus_roots.h"

int main()
{

    bplus_roots_t *bpr = read_bplus_roots();
    //print_bplus_roots(bpr);
    
    
    search_bplus_range(bpr->user, TABLE_TYPE_USER, 4, 5);
    
    
    free_bplus_roots(bpr);
    
    return 0;
    
}
