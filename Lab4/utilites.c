//
// Created by Katherina on 18.10.2020.
//

#include "./linked_list.h"
#include "./utilites.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

#include "./higher_order_func.h"

bool save(struct LinkedList *list, const char *filename) {
    FILE *file;
    file = fopen(filename, "w");
    if (file == NULL) {
        return false;
    }
    while (list != NULL) {
        fprintf(file, "%"PRId64" ", list->value);
        list = list->next;
    }
    fclose(file);
    return true;
}

bool load(struct LinkedList **list, const char *filename) {
    FILE *file;
    int64_t container;
    if ((file = fopen(filename, "r")) == NULL) {
        return false;
    }
    while (fscanf(file, "%"PRId64" ", &container) != EOF) {
        list_add_back(list, container);
    }
    fclose(file);
    return true;
}

bool serialize(struct LinkedList *list, const char *filename) {
    FILE *bin;
    if ((bin = fopen(filename, "wb")) == NULL) {
        return false;
    }
    while (list != NULL) {
        fwrite(&(list->value), sizeof(int64_t), 1, bin);
        list = list->next;
    }
    fclose(bin);
    return true;
}

bool deserialize(struct LinkedList **list, const char *filename) {
    FILE *bin;
    int64_t container;
    if ((bin = fopen(filename, "rb")) == NULL) {
        return false;
    }
    while (fread(&container, sizeof(int64_t), 1, bin) != 0) {
        \
        list_add_back(list, container);
    }
    fclose(bin);
    return true;
}
