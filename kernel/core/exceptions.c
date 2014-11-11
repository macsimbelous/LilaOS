/* Copyright (C) 2004 Белоус Максим Юрьевич. */
#include <stdlib.h>
/* Исключение 0, деление на 0, тип исключения ошибка*/
void do_divide_error_exception(){
    printf("Divide Error Exception\n");
    for(;;);
    return;
    }
/* Исключение 1, отладочное прерывание, тип исключения ловушка или ошибка */
void do_debug_exception(){
    printf("Debug Exception\n");
    for(;;);
    return;
    }
/* Исключение 2, немаскируемое прерывание, тип исключения ошибка*/
void do_nmi(){
    printf("Nmi Exception\n");
    return;
    }
/* Исключение 3, точка останова, тип исключения  ловушка*/
void do_breakpoint_exception(){
    printf("Breakpoint Exception\n");
    return;
    }
/* Исключение 4, переполнение, тип исключения ловушка*/
void do_overflow_exception(){
    printf("Overflow Exception\n");
    return;
    }
/* Исключение 5, выход за допустимые границы при BOUND, тип исключения ошибка*/
void do_bound_range_exceeded_exception(){
    printf("Bound Range Exceeded Exception\n");
    for(;;);
    return;
    }
/* Исключение 6, неправильная инструкция, тип исключения ошибка*/
void do_invalid_opcode_exception(){
    printf("Invalid Opcode Exception\n");
    for(;;);
    return;
    }
/* Исключение 7, математический сопроцессор не доступен, тип исключения ошибка*/
void do_no_math(){
    printf("No Math\n");
    for(;;);
    return;
    }
/* Исключение 8, двойная ошибка, тип исключения авария*/
void do_double_fault_exception(unsigned int error_code){
    printf("Double Fault Exception\n");
    for(;;);
    return;
    }
/* Исключение 9, работает только на i386, тип исключения ошибка*/
void do_coprocessor_segment_overrun(unsigned int error_code){
    printf("Coprocessor Segment Overrun\n");
    for(;;);
    return;
    }
/* Исключение 10, ошибочный TSS, тип исключения ошибка*/
void do_invalid_tss(unsigned int error_code){
    printf("Invalid TSS\n");
    for(;;);
    return;
    }
/* Исключение 11, Несуществующий сегмент, тип исключения ошибка*/
void do_segment_not_present(unsigned int error_code){
    printf("Segment Not Present\n");
    for(;;);
    return;
    }
/* Исключение 12, ошибка стека, тип исключения ошибка*/
void do_stack_fault_exception(unsigned int error_code){
    printf("Stack Fault Exception\n");
    for(;;);
    return;
    }
/* Исключение 13, общее исключение защиты, тип исключения ошибка*/
void do_general_protection_exception(unsigned int error_code){
    printf("General Protection Exception\n");
    for(;;);
    return;
    }
/* Исключение 14, ошибка страничной адресации, тип исключения ошибка*/
void do_page_fault_exception(unsigned int error_code){
    printf("Page Fault Exception\n");
    for(;;);
    return;
    }
/* Исключение 16, ошибка сопроцессора, тип исключения ошибка*/
void do_fpu_error(){
    printf("FPU Error\n");
    for(;;);
    return;
    }
/* Исключение 17, ошибка выравнивания, тип исключения ошибка*/
void do_alignment_check_exception(unsigned int error_code){
    printf("Alignment Check Exception\n");
    for(;;);
    return;
    }
/* Исключение 18, машинно-зависимая ошибка, тип исключения авария*/
void do_machine_check_exception(){
    printf("Machine Check Exception\n");
    for(;;);
    return;
    }
/* Исключение 19, ошибка SSE/SSE2, тип исключения ошибка*/
void do_simd_floating_point_exception(){
    printf("SIMD Floating Point Exception\n");
    for(;;);
    return;
    }
/* Исключения 15 и 20-31, заглушка для зарезервированных прерываний*/
void do_reserved_exception(){
    printf("Reserved\n");
    return;
    }

