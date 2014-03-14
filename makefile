all: make_tables sort_tables query_a query_b query_c query_d bplus_query_a emancipate_tables emancipate_bplus make_bplus_trees


make_tables: make_tables.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o make_tables make_tables.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c
sort_tables: sort_tables.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o sort_tables sort_tables.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c


query_a: query_a.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o query_a query_a.c user.c message.c timestamp.c city.c state.c record.c file_count.c
query_b: query_b.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o query_b query_b.c user.c message.c timestamp.c city.c state.c record.c file_count.c
query_c: query_c.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o query_c query_c.c user.c message.c timestamp.c city.c state.c record.c file_count.c
query_d: query_d.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o query_d query_d.c user.c message.c timestamp.c city.c state.c record.c file_count.c


refactored_query_a: refactored_query_a.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o refactored_query_a query_a.c user.c message.c timestamp.c city.c state.c record.c file_count.c
refactored_query_b: refactored_query_b.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o refactored_query_b query_b.c user.c message.c timestamp.c city.c state.c record.c file_count.c
refactored_query_c: refactored_query_c.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o refactored_query_c query_c.c user.c message.c timestamp.c city.c state.c record.c file_count.c
refactored_query_d: refactored_query_d.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o refactored_query_d query_d.c user.c message.c timestamp.c city.c state.c record.c file_count.c

bplus_query_a: bplus_query_a.c int_node.c search_tree.c state.c; gcc -o bplus_query_a bplus_query_a.c int_node.c search_tree.c state.c -lm

emancipate_tables: emancipate_tables.c; gcc -o emancipate_tables emancipate_tables.c
emancipate_bplus: emancipate_bplus.c; gcc -o emancipate_bplus emancipate_bplus.c


make_bplus_trees: make_bplus_trees.c int_node.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c bplus_roots.c; gcc -o make_bplus_trees make_bplus_trees.c int_node.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c bplus_roots.c


test: test.c int_node.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c bplus_roots.c; gcc -o test test.c int_node.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c bplus_roots.c
