#include "./linked_list.h"
#include <stdlib.h>
#include <stdint.h>

#ifndef H_HIGHER_ORDER_FUNC
#define H_HIGHER_ORDER_FUNC

void foreach(struct LinkedList *list, void (*func)(int64_t));

struct LinkedList *map(struct LinkedList *origin, int64_t (*func)(int64_t));

void map_mut(struct LinkedList **origin, int64_t (*func)(int64_t));

int64_t foldl(int64_t accum, struct LinkedList *list, int64_t (*func)(int64_t, int64_t));

struct LinkedList *iterate(int64_t s, size_t n, int64_t (*func)(int64_t));

#endif
