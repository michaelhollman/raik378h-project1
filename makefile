make_tables: make_tables.c user.c message.c timestamp.c datestamp.c city.c state.c record.c; gcc -o make_tables make_tables.c user.c message.c timestamp.c datestamp.c city.c state.c record.c
test: test.c user.c message.c timestamp.c datestamp.c location.c record.c; gcc -o test test.c user.c message.c timestamp.c datestamp.c city.c state.c record.c
query_a: query_a.c user.c message.c timestamp.c datestamp.c city.c state.c record.c; gcc -o query_a query_a.c user.c message.c timestamp.c city.c state.c record.c
query_b: query_b.c user.c message.c timestamp.c datestamp.c city.c state.c record.c; gcc -o query_b query_b.c user.c message.c timestamp.c city.c state.c record.c
query_c: query_c.c user.c message.c timestamp.c datestamp.c city.c state.c record.c; gcc -o query_c query_c.c user.c message.c timestamp.c city.c state.c record.c
query_d: query_d.c user.c message.c timestamp.c datestamp.c city.c state.c record.c; gcc -o query_d query_d.c user.c message.c timestamp.c city.c state.c record.c
emancipate_files: emancipate_files.c ;gcc -o emancipate_files emancipate_files.c