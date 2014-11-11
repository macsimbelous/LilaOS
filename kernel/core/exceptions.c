/* Copyright (C) 2004 ������ ������ �������. */
#include <stdlib.h>
/* ���������� 0, ������� �� 0, ��� ���������� ������*/
void do_divide_error_exception(){
    printf("Divide Error Exception\n");
    for(;;);
    return;
    }
/* ���������� 1, ���������� ����������, ��� ���������� ������� ��� ������ */
void do_debug_exception(){
    printf("Debug Exception\n");
    for(;;);
    return;
    }
/* ���������� 2, ������������� ����������, ��� ���������� ������*/
void do_nmi(){
    printf("Nmi Exception\n");
    return;
    }
/* ���������� 3, ����� ��������, ��� ����������  �������*/
void do_breakpoint_exception(){
    printf("Breakpoint Exception\n");
    return;
    }
/* ���������� 4, ������������, ��� ���������� �������*/
void do_overflow_exception(){
    printf("Overflow Exception\n");
    return;
    }
/* ���������� 5, ����� �� ���������� ������� ��� BOUND, ��� ���������� ������*/
void do_bound_range_exceeded_exception(){
    printf("Bound Range Exceeded Exception\n");
    for(;;);
    return;
    }
/* ���������� 6, ������������ ����������, ��� ���������� ������*/
void do_invalid_opcode_exception(){
    printf("Invalid Opcode Exception\n");
    for(;;);
    return;
    }
/* ���������� 7, �������������� ����������� �� ��������, ��� ���������� ������*/
void do_no_math(){
    printf("No Math\n");
    for(;;);
    return;
    }
/* ���������� 8, ������� ������, ��� ���������� ������*/
void do_double_fault_exception(unsigned int error_code){
    printf("Double Fault Exception\n");
    for(;;);
    return;
    }
/* ���������� 9, �������� ������ �� i386, ��� ���������� ������*/
void do_coprocessor_segment_overrun(unsigned int error_code){
    printf("Coprocessor Segment Overrun\n");
    for(;;);
    return;
    }
/* ���������� 10, ��������� TSS, ��� ���������� ������*/
void do_invalid_tss(unsigned int error_code){
    printf("Invalid TSS\n");
    for(;;);
    return;
    }
/* ���������� 11, �������������� �������, ��� ���������� ������*/
void do_segment_not_present(unsigned int error_code){
    printf("Segment Not Present\n");
    for(;;);
    return;
    }
/* ���������� 12, ������ �����, ��� ���������� ������*/
void do_stack_fault_exception(unsigned int error_code){
    printf("Stack Fault Exception\n");
    for(;;);
    return;
    }
/* ���������� 13, ����� ���������� ������, ��� ���������� ������*/
void do_general_protection_exception(unsigned int error_code){
    printf("General Protection Exception\n");
    for(;;);
    return;
    }
/* ���������� 14, ������ ���������� ���������, ��� ���������� ������*/
void do_page_fault_exception(unsigned int error_code){
    printf("Page Fault Exception\n");
    for(;;);
    return;
    }
/* ���������� 16, ������ ������������, ��� ���������� ������*/
void do_fpu_error(){
    printf("FPU Error\n");
    for(;;);
    return;
    }
/* ���������� 17, ������ ������������, ��� ���������� ������*/
void do_alignment_check_exception(unsigned int error_code){
    printf("Alignment Check Exception\n");
    for(;;);
    return;
    }
/* ���������� 18, �������-��������� ������, ��� ���������� ������*/
void do_machine_check_exception(){
    printf("Machine Check Exception\n");
    for(;;);
    return;
    }
/* ���������� 19, ������ SSE/SSE2, ��� ���������� ������*/
void do_simd_floating_point_exception(){
    printf("SIMD Floating Point Exception\n");
    for(;;);
    return;
    }
/* ���������� 15 � 20-31, �������� ��� ����������������� ����������*/
void do_reserved_exception(){
    printf("Reserved\n");
    return;
    }

