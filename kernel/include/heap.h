/* Copyright (C) 2004 Белоус Максим Юрьевич. */
#ifndef HEAP_H
#define HEAP_H

#include <types.h>

struct _slab_t{
    unsigned int size;
    unsigned int used;
    void * next;
    void * previous;
};
typedef struct _slab_t * slab_t;

struct _heap_t{
    void * slab_root;
    unsigned int options;
    unsigned int size;
    void *  next_heap;
};
typedef struct _heap_t * heap_t;
   
heap_t heap_create(unsigned int size, unsigned int options);
void * heap_alloc(heap_t heap_info, unsigned int size);
void heap_free(heap_t heap_info, void * address);
void init_heap();
void dump_heap_info(heap_t heap);
void * malloc(unsigned int size);
void free(void * address);

#define USED_SLAB 1
#define FREE_SLAB 0

#endif
