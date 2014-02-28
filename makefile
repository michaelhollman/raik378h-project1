all: make_tables sort_tables query_a query_b query_c query_d emancipate_files

make_tables: make_tables.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o make_tables make_tables.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c
sort_tables: sort_tables.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o sort_tables sort_tables.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c
test: test.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o test test.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c
query_a: query_a.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o query_a query_a.c user.c message.c timestamp.c city.c state.c record.c file_count.c
query_b: query_b.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o query_b query_b.c user.c message.c timestamp.c city.c state.c record.c file_count.c
query_c: query_c.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o query_c query_c.c user.c message.c timestamp.c city.c state.c record.c file_count.c
query_d: query_d.c user.c message.c timestamp.c datestamp.c city.c state.c record.c file_count.c; gcc -o query_d query_d.c user.c message.c timestamp.c city.c state.c record.c file_count.c
emancipate_files: emancipate_files.c ;gcc -o emancipate_files emancipate_files.c