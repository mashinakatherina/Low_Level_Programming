#include "./linked_list.h"
#include "./higher_order_func.h"
#include "./utilites.h"
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <inttypes.h>

void print_space(int64_t);

void print_new(int64_t);

int64_t square(int64_t);

int64_t cube(int64_t);

int64_t multiply(int64_t x, int64_t a);

int64_t twoTimes(int64_t x);

void basic_test(struct LinkedList *list);

struct LinkedList *initial(void);

void foreach_test(struct LinkedList *list);

void map_test(struct LinkedList *list);

void map_mut_test(struct LinkedList *list);

void foldl_test(struct LinkedList *list);

struct LinkedList *iterate_test(void);

void file_test(struct LinkedList **list);

void file_bin_test(struct LinkedList **list);


enum status {
    Ok,
    ErrorInSerialization,
    ErrorInDeserialization,
    ErrorInSaving,
    ErrorInLoading
};

struct LinkedList *initial(void) {
    int64_t digit;
    struct LinkedList *list;

    printf("write your numbers: ");
    if (scanf("%" PRId64 "", &digit) != EOF) {
        list = list_create(digit);
        while (scanf("%" PRId64 "", &digit) != EOF) {
            list_add_front(&list, digit);
        }
    }
    return list;
}

void foreach_test(struct LinkedList *list) {
    puts("foreach with spaces");
    foreach(list, print_space);
    puts("\nforeach with new line");
    foreach(list, print_new);
}

void basic_test(struct LinkedList *list) {
    int64_t second = list_get(list, 2);
    size_t len = list_length(list);
    struct LinkedList *third = list_node_at(list, 3);
    int64_t sum = list_sum(list);
    printf("length -> %lu\nsum -> %"PRId64"\n", len, sum);
    if ((second != 0) && (third != NULL)) {
        printf("list_get second -> %"PRId64"\nlist_node_at third %"PRId64"\n",
               second,
               third->value);
    } else {
        puts("Exception in list_node_at or list_get");
    }
}

void file_test(struct LinkedList **iter) {
    puts("saving in file");
    if (!save(*iter, "myfile")) {
        puts("file_error");
        exit(ErrorInSaving);
    };
    puts("saved");

    list_free(*iter);
    *iter = NULL;

    puts("loading from file");
    if (!load(iter, "myfile")) {
        puts("load error");
        exit(ErrorInLoading);
    }
    printf("load is complited, list is -> ");

    foreach(*iter, print_space);
    puts("");

}

void file_bin_test(struct LinkedList **iter) {
    puts("serialization");
    if (!serialize(*iter, "./myfilebin.bin")) {
        puts("bin file error");
        exit(ErrorInSerialization);
    };
    puts("serialization complite");

    list_free(*iter);
    *iter = NULL;

    puts("deserialization");
    if (!deserialize(iter, "./myfilebin.bin")) {
        puts("bin file error");
        exit(ErrorInDeserialization);
    }
    printf("deserialization complite, list is -> ");
    foreach(*iter, print_space);
    puts("");

}

struct LinkedList *iterate_test(void) {
    struct LinkedList *iter = iterate(1, 10, twoTimes);
    puts("iteration");
    foreach(iter, print_space);
    puts("");
    return iter;
}

void foldl_test(struct LinkedList *list) {
    int64_t su = foldl(0, list, multiply);
    printf("foldl sum-> %"PRId64"\n", su);
}

void map_mut_test(struct LinkedList *list) {
    map_mut(&list, imaxabs);
    puts("map_mut abs");
    foreach(list, print_space);
    puts("");
}

void map_test(struct LinkedList *list) {
    struct LinkedList *squares = map(list, square);
    struct LinkedList *cubes = map(list, cube);

    puts("map square");
    foreach(squares, print_space);
    puts("");

    puts("map cubes");
    foreach(cubes, print_space);
    puts("");

    list_free(squares);
    list_free(cubes);
}

void print_space(int64_t i) {
    printf("%" PRId64 " ", i);
}

void print_new(int64_t i) {
    printf("%" PRId64 "\n", i);
}

int64_t square(int64_t x) {
    return x * x;
}

int64_t cube(int64_t x) {
    return x * x * x;
}

int64_t multiply(int64_t x, int64_t a) {
    return x * a;
}

int64_t twoTimes(int64_t x) {
    return 2 * x;
}

int main() {
    struct LinkedList *list = initial();

    basic_test(list);

    foreach_test(list);

    map_test(list);

    map_mut_test(list);

    foldl_test(list);

    struct LinkedList *iter = iterate_test();

    file_test(&iter);

    file_bin_test(&iter);

    list_free(list);

    list_free(iter);
    return Ok;
}