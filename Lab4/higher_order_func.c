#include "./linked_list.h"
#include "./higher_order_func.h"
#include <stddef.h>
#include <stdint.h>

void foreach(struct LinkedList *list, void (*func)(int64_t)) {
    while (list != NULL) {
        func(list->value);
        list = list->next;
    }
}

struct LinkedList *map(struct LinkedList *origin, int64_t (*func)(int64_t)) {
    struct LinkedList *head = NULL;
    while (origin != NULL) {
        list_add_front(&head, func(origin->value));
        origin = origin->next;
    }
    return head;
}

void map_mut(struct LinkedList **origin, int64_t (*func)(int64_t)) {
    if ((*origin) == NULL)
        return;
    (*origin)->value = func((*origin)->value);
    map_mut(&(*origin)->next, func);
    return;
}

int64_t foldl(int64_t accum, struct LinkedList *list, int64_t (*func)(int64_t, int64_t)) {
    while (list != NULL) {
        accum = func(list->value, accum);
        list = list->next;
    }
    return accum;
}

struct LinkedList *iterate(int64_t s, size_t n, int64_t (*func)(int64_t)) {
    struct LinkedList *list = list_create(s);
    n--;
    for (unsigned int i = 0; i < n; i++) {
        s = func(s);
        list_add_back(&list, s);
    }
    return list;
}
