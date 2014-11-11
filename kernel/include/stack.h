/* Copyright (C) 2004 ������ ������ �������. */
#ifndef _STACK_H
#define _STACK_H

struct _stack_t{
    /* ������ ������ ���������. */
    unsigned int size;
    /* ��������� ������� �����. */
    unsigned int pointer;
    /* ��������� �� ����� �����. */
    unsigned int * buffer;
};
typedef struct _stack_t * stack_t;

stack_t create_stack(unsigned int size);
unsigned int pop_stack(stack_t stack);
void push_stack(stack_t stack, unsigned int value);
unsigned int get_size_stack(stack_t stack);
unsigned int get_free_stack(stack_t stack);

#endif

