#ifndef LAB7_ALLOCATION_H
#define LAB7_ALLOCATION_H

#include <stdbool.h>
#include <stddef.h>

#define MIN_BLOCK_SIZE 32

void *HEAP_START;

typedef struct __attribute__((packed)) {
    struct header *next;
    size_t capacity;
    bool is_free;
} header;

void *init(size_t init_size);

void *_malloc(size_t query);

void _free(void *p);

#endif //LAB7_ALLOCATION_H
