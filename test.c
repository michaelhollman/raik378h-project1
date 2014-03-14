#include <string.h>
#include <stdio.h>

#include "int_node.h"
#include "bplus_roots.h"

int main()
{

    bplus_roots_t *bpr = read_bplus_roots();
    print_bplus_roots(bpr);
    
    
    search_bplus(bpr->timestamp, TABLE_TYPE_TIMESTAMP, 800);
    
    
    free_bplus_roots(bpr);
    
    return 0;
}
