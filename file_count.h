#ifndef _file_count_h
#define _file_count_h

typedef struct {
    int users;
    int cities;
    int states;
    int messages;
    int timestamps;
    int datestamps;
} file_count_t;

void print_file_count(file_count_t *fc);

file_count_t *read_file_count();

void write_file_count(file_count_t *fc);

void free_file_count(file_count_t *fc);

#endif
