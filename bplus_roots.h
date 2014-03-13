#ifndef _bplus_roots_h
#define _bplus_roots_h

typedef struct {
    int user;
    int city;
    int state;
    int message;
    int timestamp;
    int datestamp;
} bplus_roots_t;

void print_bplus_roots(bplus_roots_t *bpr);

bplus_roots_t *read_bplus_roots();

void write_bplus_roots(bplus_roots_t *bpr);

void free_bplus_roots(bplus_roots_t *bpr);

#endif
