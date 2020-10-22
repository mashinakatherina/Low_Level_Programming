#include "./linked_list.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

struct LinkedList *list_create(int64_t value) {
    struct LinkedList *head = NULL;
    list_add_front(&head, value);
    return head;
}

void list_add_front(struct LinkedList **head, int64_t value) {
    struct LinkedList *tmp = (struct LinkedList *) malloc(sizeof(struct LinkedList));
    tmp->value = value;
    tmp->next = (*head);
    (*head) = tmp;
}

void list_add_back(struct LinkedList **head, int64_t value) {
    if (*head == NULL) {
        list_add_front(head, value);
        return;
    }
    struct LinkedList *tmp = (*head);
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    struct LinkedList *newNode = (struct LinkedList *) malloc(sizeof(struct LinkedList));
    newNode->next = NULL;
    newNode->value = value;
    tmp->next = newNode;
}

int64_t list_get(struct LinkedList *head, size_t index) {
    if ((head = list_node_at(head, index)) == NULL)
        return 0;
    return head->value;
}

void list_free(struct LinkedList *head) {
    if (head == NULL)
        return;
    list_free(head->next);
    free(head);
}

size_t list_length(struct LinkedList *head) {
    size_t length = 0;
    while (head != NULL) {
        length++;
        head = head->next;
    }
    return length;
}

struct LinkedList *list_node_at(struct LinkedList *head, size_t index) {
    for (unsigned int i = index; i > 0; i--) {
        if (head == NULL)
            return NULL;
        head = head->next;
    }
    return head;
}

int64_t list_sum(struct LinkedList *head) {
    int64_t sum = 0;
    while (head != NULL) {
        sum += head->value;
        head = head->next;
    }
    return sum;
}
