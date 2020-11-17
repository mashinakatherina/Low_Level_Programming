#include <stdbool.h>
#include <stdio.h>
#include "allocation.h"
#include <sys/mman.h>

void *init(size_t init_size) {
    if (init_size < sizeof(header))
        return NULL;

    HEAP_START = mmap(NULL, init_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (HEAP_START == MAP_FAILED)
        return NULL;

    header header_p;
    header_p.next = NULL;
    header_p.capacity = init_size;
    header_p.is_free = true;

    *(header *) HEAP_START = header_p;
}

void *_malloc(size_t query) {
    if (MIN_BLOCK_SIZE <= 0) {
        return NULL;
    }

    if (query < MIN_BLOCK_SIZE) {
        query = MIN_BLOCK_SIZE;
    }

    header *block = (header *) HEAP_START;

    while (true) {
        if (block->is_free && query < block->capacity - sizeof(header) -
                                      MIN_BLOCK_SIZE) { 
            size_t temp_size = block->capacity - query - sizeof(header);   
            header *new = (header *) ((void *) block +
                                      block->capacity);      
            *new = *block;                                                
            new->capacity = temp_size;
            block->capacity = query + sizeof(header);
            block->is_free = false;
            block->next = (void *) new;
            void *place =
                    (void *) block + sizeof(header);                   
            return place;
        }

        if (!block->next) {                                                 
            void *p = mmap((void *) block + block->capacity, query, PROT_READ | PROT_WRITE,
                           MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1,
                           0); 
            if (p == MAP_FAILED) {
                p = mmap(NULL, query, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
                if (p == MAP_FAILED)
                    return NULL;
            }
            header header_p;
            header_p.next = NULL;
            header_p.capacity = query;
            header_p.is_free = false;
            *(header *) p = header_p;
            block->next = p;
            return p + sizeof(header_p);
        }

        block = (header *) block->next;
    }

}

void _free(void *p) {
    p -= sizeof(header);
    header *head = (header *) p;
    head->is_free = true; 

    while (head->next != NULL && ((header *) (head->next))->is_free) {
        head->capacity += ((header *) (head->next))->capacity + sizeof(header);
        head->next = ((header *) (head->next))->next;
    }
}
