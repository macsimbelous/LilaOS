/* Copyright (C) 2004 Белоус Максим Юрьевич. */
#ifndef _STACK_H
#define _STACK_H

struct _stack_t{
    /* размер стекав элементах. */
    unsigned int size;
    /* Указатель вершины стека. */
    unsigned int pointer;
    /* Указатель на буфер стека. */
    unsigned int * buffer;
};
typedef struct _stack_t * stack_t;

stack_t create_stack(unsigned int size);
unsigned int pop_stack(stack_t stack);
void push_stack(stack_t stack, unsigned int value);
unsigned int get_size_stack(stack_t stack);
unsigned int get_free_stack(stack_t stack);

#endif

