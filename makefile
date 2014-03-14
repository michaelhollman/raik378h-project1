all: make_tables sort_tables query_a query_b query_c query_d bplus_query_a emancipate_tables emancipate_bplus make_bplus_trees

clean:; rm make_tables; rm sort_tables; rm query_a; rm query_b;  rm query_c; rm query_d; rm emancipate_tables; rm emancipate_bplus; rm make_bplus_trees; rm test;

make_tables: make_tables.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o make_tables make_tables.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c -lm -std=c99
sort_tables: sort_tables.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o sort_tables sort_tables.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c


query_a: query_a.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o query_a query_a.c user.c message.c timestamp.c city.c state.c record.c file_count.c
query_b: query_b.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o query_b query_b.c user.c message.c timestamp.c city.c state.c record.c file_count.c
query_c: query_c.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o query_c query_c.c user.c message.c timestamp.c city.c state.c record.c file_count.c
query_d: query_d.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o query_d query_d.c user.c message.c timestamp.c city.c state.c record.c file_count.c


refactored_query_a: refactored_query_a.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o refactored_query_a query_a.c user.c message.c timestamp.c city.c state.c record.c file_count.c
refactored_query_b: refactored_query_b.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o refactored_query_b query_b.c user.c message.c timestamp.c city.c state.c record.c file_count.c
refactored_query_c: refactored_query_c.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o refactored_query_c query_c.c user.c message.c timestamp.c city.c state.c record.c file_count.c
refactored_query_d: refactored_query_d.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o refactored_query_d query_d.c user.c message.c timestamp.c city.c state.c record.c file_count.c

bplus_query_a: bplus_query_a.c int_node.c bplus_roots.c state.c; gcc -o bplus_query_a bplus_roots.c bplus_query_a.c int_node.c state.c -lm -std=c99
bplus_query_b: bplus_query_b.c int_node.c bplus_roots.c timestamp.c file_count.c message.c; gcc -o bplus_query_b bplus_query_b.c int_node.c bplus_roots.c timestamp.c file_count.c message.c -lm -std=c99
bplus_query_c: bplus_query_c.c int_node.c bplus_roots.c timestamp.c file_count.c message.c user.c state.c; gcc -o bplus_query_c bplus_query_c.c int_node.c bplus_roots.c timestamp.c file_count.c message.c user.c state.c -lm -std=c99
bplus_query_d: bplus_query_d.c int_node.c bplus_roots.c timestamp.c file_count.c message.c user.c state.c; gcc -o bplus_query_d bplus_query_d.c int_node.c bplus_roots.c timestamp.c file_count.c message.c user.c state.c -lm -std=c99

emancipate_tables: emancipate_tables.c; gcc -o emancipate_tables emancipate_tables.c
emancipate_bplus: emancipate_bplus.c; gcc -o emancipate_bplus emancipate_bplus.c


make_bplus_trees: make_bplus_trees.c int_node.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c bplus_roots.c; gcc -o make_bplus_trees make_bplus_trees.c int_node.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c bplus_roots.c -lm -std=c99


test: test.c int_node.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c bplus_roots.c; gcc -o test test.c int_node.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c bplus_roots.c
