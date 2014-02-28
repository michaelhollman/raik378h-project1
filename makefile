make_tables: make_tables.c user.c message.c timestamp.c location.c record.c; gcc -o make_tables make_tables.c user.c message.c timestamp.c location.c record.c
test: test.c user.c message.c timestamp.c location.c record.c; gcc -o test test.c user.c message.c timestamp.c location.c record.c
query_a: query_a.c user.c message.c timestamp.c location.c record.c; gcc -o query_a query_a.c user.c message.c timestamp.c location.c record.c
query_b: query_b.c user.c message.c timestamp.c location.c record.c; gcc -o query_b query_b.c user.c message.c timestamp.c location.c record.c
