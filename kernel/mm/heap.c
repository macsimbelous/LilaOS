/* Copyright (C) 2004 Белоус Максим Юрьевич. */
#include <types.h>
#include <heap.h>
#include <stdlib.h>
#include <pmm.h>
#include <ints.h>

heap_t kernel_heap;

void init_heap(){
    kernel_heap = heap_create(100 * KB, 0);
    if(kernel_heap == NULL){
        printf("Heap error\n");
        for(;;);
    }
    printf("Init Heap Memory\n");
}

void dump_heap_info(heap_t heap){
    slab_t slab;
    printf("\n\r HEAP :: Dump - ");
    disable_ints();
    slab = heap->slab_root;
    while(slab == NULL){
        printf("    address %X, size %u", (unsigned int)slab, slab->size);
        if(slab->used == USED_SLAB){
                printf(", USED");
        }else{
                printf(", FREE");
        }
        slab=slab->next;
    }
    enable_ints();
}
heap_t heap_create(unsigned int size, unsigned int options){
    slab_t slab;
    unsigned int req_pages=(size+sizeof(struct _heap_t))/PAGE_SIZE+1;
    heap_t heap=(heap_t)alloc_pages(req_pages);
    if ( heap == NULL )
        return NULL;
    heap->size = req_pages;
    heap->options=options;
    heap->next_heap=NULL;
    heap->slab_root=(struct slab_t*)((unsigned int)heap + sizeof(struct _heap_t));
    slab = heap->slab_root;
    slab->size = req_pages - sizeof(struct _heap_t);
    slab->used = FREE_SLAB;
    slab->previous = NULL;
    slab->next = NULL;
    return heap;
}

void * heap_alloc(heap_t heap_info, unsigned int size){
    slab_t temp;
    disable_ints();
    slab_t slab = heap_info->slab_root;
    size += sizeof(struct _slab_t);
    if (heap_info == NULL)
        return NULL;
    if (size == 0)
        return NULL;
    while(slab){
        if(slab->used == FREE_SLAB && slab->size > size)
            break;
        if(slab->next == NULL)
                return NULL;
        slab = slab->next;
    }
    if(slab->size > (size + sizeof(struct _slab_t) + 1)){
        temp = (slab_t)(((unsigned int)slab) + size);
        temp->size = slab->size - size;
        temp->used = FREE_SLAB;
        temp->next = slab->next;
        temp->previous = slab;
        slab->size = size;
        slab->used = USED_SLAB;
        slab->next = temp;
        enable_ints();
        return (void *)(((unsigned int)slab) + sizeof(struct _slab_t));
    }else{
        slab->used = USED_SLAB;
        enable_ints();
        return (void *)(((unsigned int)slab) + sizeof(struct _slab_t));
    }
}

void heap_free(heap_t heap_info, void * address){
    slab_t temp;
    slab_t slab;
    disable_ints();
    slab = (slab_t)((unsigned int)address - sizeof(struct _slab_t));
    temp = slab->previous;
    if(temp->used == FREE_SLAB){
        temp->next = slab->next;
        temp->used = FREE_SLAB;
        temp->size = temp->size + slab->size;
        slab = temp;
    }
    temp = slab->next;
    if(temp->used == FREE_SLAB){
        slab->next = temp->next;
        slab->size = slab->size + temp->size;
    }
    enable_ints();
    return;
}

void * malloc(unsigned int size){
    return heap_alloc(kernel_heap, size);
}

void free(void * address){
    return heap_free(kernel_heap, address);
}
