//
// Created by Katherina on 18.10.2020.
//

#include "./linked_list.h"
#include <stdbool.h>

#ifndef H_UTIL
#define H_UTIL

bool save(struct LinkedList *list, const char *filename);

bool load(struct LinkedList **list, const char *filename);

bool serialize(struct LinkedList *list, const char *filename);

bool deserialize(struct LinkedList **list, const char *filename);

#endif

