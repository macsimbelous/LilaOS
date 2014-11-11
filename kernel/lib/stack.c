/* Copyright (C) 2004 ������ ������ �������. */
#include <stdlib.h>
#include <stack.h>
#include <heap.h>

/* ������� ������ ����. */
stack_t create_stack(unsigned int size){
    stack_t temp;
    temp = (stack_t)malloc(sizeof(struct _stack_t));
    if(temp == NULL){
        printf("Create stack failed 1\n");
        return NULL;
    }
    temp->buffer = malloc(size * 4);
    if(temp->buffer == NULL){
        printf("Create stack failed 2");
        free(temp);
        return NULL;
    }
    temp->size = size;
    temp->pointer = 0;
    return temp;
    }
/* ������� ���������� ������� ������� ����� ����� ���������� 0. */
unsigned int pop_stack(stack_t stack){
    if(stack->pointer == 0)
        return 0;
    stack->pointer--;
    return stack->buffer[stack->pointer];
    }
/* ������� ����� ������� �� ������� �����. */
void push_stack(stack_t stack, unsigned int value){
    if(stack->pointer >= stack->size)
        return;
    stack->buffer[stack->pointer] = value;
    stack->pointer++;
    return;
    }
/* ���������� ������ ����� � ���������. */
unsigned int get_size_stack(stack_t stack){
    return stack->size;
    }
/* ���������� ���������� ��������� ��������� �����. */
unsigned int get_free_stack(stack_t stack){
    return (stack->size - stack->pointer - 1);
    }

