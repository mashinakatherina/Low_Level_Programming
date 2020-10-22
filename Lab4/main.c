#include "./linked_list.h"
#include "./higher_order_func.h"
#include "./utilites.h"
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <inttypes.h>

static void print_space(int64_t);

static void print_new(int64_t);

static int64_t square(int64_t);

static int64_t cube(int64_t);

static int64_t summa(int64_t x, int64_t a);

static int64_t two(int64_t);

static void basic_test(struct LinkedList *list);

static struct LinkedList *initial(void);

static void foreach_test(struct LinkedList *list);

static void map_test(struct LinkedList *list);

static void map_mut_test(struct LinkedList *list);

static void foldl_test(struct LinkedList *list);

static struct LinkedList *iterate_test(void);

static void file_test(struct LinkedList **list);

static void file_bin_test(struct LinkedList **list);


enum status {
    Ok,
    ErrorInSerialization,
    ErrorInDeserialization,
    ErrorInSaving,
    ErrorInLoading
};

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


static struct LinkedList *initial(void) {
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

static void foreach_test(struct LinkedList *list) {
    puts("foreach with spaces");
    foreach(list, print_space);
    puts("\nforeach with new line");
    foreach(list, print_new);
}

static void basic_test(struct LinkedList *list) {
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
        puts("something went wrong with list_node_at or list_get");
    }
}

static void file_test(struct LinkedList **iter) {
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

static void file_bin_test(struct LinkedList **iter) {
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

static struct LinkedList *iterate_test(void) {
    struct LinkedList *iter = iterate(1, 10, two);
    puts("iteration");
    foreach(iter, print_space);
    puts("");
    return iter;
}

static void foldl_test(struct LinkedList *list) {
    int64_t su = foldl(0, list, summa);
    printf("foldl sum-> %"PRId64"\n", su);
}

static void map_mut_test(struct LinkedList *list) {
    map_mut(&list, imaxabs);
    puts("map_mut abs");
    foreach(list, print_space);
    puts("");
}

static void map_test(struct LinkedList *list) {
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

static void print_space(int64_t i) {
    printf("%" PRId64 " ", i);
}

static void print_new(int64_t i) {
    printf("%" PRId64 "\n", i);
}

static int64_t square(int64_t x) {
    return x * x;
}

static int64_t cube(int64_t x) {
    return x * x * x;
}

static int64_t summa(int64_t x, int64_t a) {
    return x + a;
}

static int64_t two(int64_t x) {
    return 2 * x;
}
