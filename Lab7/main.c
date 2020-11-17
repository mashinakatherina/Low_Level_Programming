//
// Created by Katherina on 17.11.2020.
//

#include <stdio.h>
#include "allocation.h"
#include "mem_debug.h"

#define MIN_BLOCK_SIZE 1

int main() {
    init(1000);

    char *a = (char *) _malloc(sizeof(char) * 10000);
    for (int i = 0; i < 10000; ++i) {
        a[i] = 64;
    }

    char *b = (char *) _malloc(sizeof(char) * 3);
    for (int i = 0; i < 3; ++i) {
        b[i] = 2;
    }

    char *c = (char *) _malloc(sizeof(char) * 1);
    c[0] = 'f';

    FILE *f = fopen("heap.txt", "w");
    memalloc_debug_heap(f, HEAP_START);

    _free(a);
    _free(c);
    _free(b);

    f = fopen("heap_after_free.txt", "w");
    memalloc_debug_heap(f, HEAP_START);
    puts("done");
    return 0;
}