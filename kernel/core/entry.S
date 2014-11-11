/*
 *  entry.S - точки входа в ядро
 *
 *  Copyright (C) 2003 Белоус Максим Юрьевич
 */
#define _ASM_ 1

#include <config.h>
#include <segments.h>
#define NR_SYS_CALL 1

.extern EXT_C(do_divide_error_exception), EXT_C(do_debug_exception), EXT_C(do_breakpoint_exception), EXT_C(do_nmi)
.extern EXT_C(do_overflow_exception), EXT_C(do_bound_range_exceeded_exception)
.extern EXT_C(do_invalid_opcode_exception), EXT_C(do_no_math), EXT_C(do_double_fault_exception)
.extern EXT_C(do_coprocessor_segment_overrun), EXT_C(do_invalid_tss), EXT_C(do_segment_not_present)
.extern EXT_C(do_stack_fault_exception), EXT_C(do_general_protection_exception), EXT_C(do_page_fault_exception)
.extern EXT_C(do_fpu_error), EXT_C(do_alignment_check_exception), EXT_C(do_machine_check_exception)
.extern EXT_C(do_simd_floating_point_exception), EXT_C(do_reserved_exception), EXT_C(default_handler_irq)
    .text
/* точка входа системных вызовов */
ENTRY(sys_call):
	cmpl	$NR_SYS_CALL-1, %eax
	ja	bad_sys_call
	pushl	%ecx
	pushl	%edx
	pushl	%ebx
	pushl	%esi
	pushl	%edi
	movl	$KERNEL_DS, %edx
	movw	%dx, %ds
	movw	%dx, %es
	call	*EXT_C(table_sys_call)(,%eax,4)
/*	movl	%eax, 28(%esp) */
	movl	$USER_DS, %edx
	movw	%dx, %ds
	movw	%dx, %es
	addl $20, %esp
/*	popl	%edi */
/*	popl	%esi */
/*	popl	%ebx */
/*	popl	%edx */
/*	popl	%ecx */
	iret
bad_sys_call:
	movl	$-1, %eax
	iret
/* точки входа исключений и немаскируемых прерываний */
/* деление на ноль */
ENTRY(divide_error_exception):
    pushl %eax
	pushl %ecx
	pushl %edx
	pushl %ebx
	pushl %esi
	pushl %edi
	call	EXT_C(do_divide_error_exception)
	popl %edi
	popl %esi
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax
	iret
/* отладка */
ENTRY(debug_exception):
	pushl %eax
	pushl %ecx
	pushl %edx
	pushl %ebx
	pushl %esi
	pushl %edi
	call	EXT_C(do_debug_exception)
	popl %edi
	popl %esi
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax
	iret
/* NMI */
ENTRY(nmi):
	pushl %eax
	pushl %ecx
	pushl %edx
	pushl %ebx
	pushl %esi
	pushl %edi
	call	EXT_C(do_nmi)
	popl %edi
	popl %esi
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax
	iret
/* контрольная точка */
ENTRY(breakpoint_exception):
	pushl %eax
	pushl %ecx
	pushl %edx
	pushl %ebx
	pushl %esi
	pushl %edi
	call	EXT_C(do_breakpoint_exception)
	popl %edi
	popl %esi
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax
	iret
/* переполнение */
ENTRY(overflow_exception):
	pushl %eax
	pushl %ecx
	pushl %edx
	pushl %ebx
	pushl %esi
	pushl %edi
	call	EXT_C(do_overflow_exception)
	popl %edi
	popl %esi
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax
	iret
/* нарушение границ массива */
ENTRY(bound_range_exceeded_exception):
	pushl %eax
	pushl %ecx
	pushl %edx
	pushl %ebx
	pushl %esi
	pushl %edi
	call	EXT_C(do_bound_range_exceeded_exception)
	popl %edi
	popl %esi
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax
	iret
/* недопустимая команда */
ENTRY(invalid_opcode_exception):
	pushl %eax
	pushl %ecx
	pushl %edx
	pushl %ebx
	pushl %esi
	pushl %edi
	call	EXT_C(do_invalid_opcode_exception)
	popl %edi
	popl %esi
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax
	iret
/* обращение к отсутствующему процессору */
ENTRY(no_math):
	pushl %eax
	pushl %ecx
	pushl %edx
	pushl %ebx
	pushl %esi
	pushl %edi
	call	EXT_C(do_no_math)
	popl %edi
	popl %esi
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax
	iret
/* двойная ошибка */
ENTRY(double_fault_exception):
    xchgl   (%esp), %eax
    pushl %ecx
	pushl %edx
	pushl %ebx
	pushl %esi
	pushl %edi
	pushl %eax
	call	EXT_C(do_double_fault_exception)
	addl	$4, %esp
	popl %edi
	popl %esi
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax
	iret
/* работает только на i386*/
ENTRY(coprocessor_segment_overrun):
	xchgl   (%esp), %eax
    pushl %ecx
	pushl %edx
	pushl %ebx
	pushl %esi
	pushl %edi
	pushl %eax
	call	EXT_C(do_coprocessor_segment_overrun)
	addl	$4, %esp
	popl %edi
	popl %esi
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax
	iret
/* неверный TSS */
ENTRY(invalid_tss):
	xchgl   (%esp), %eax
    pushl %ecx
	pushl %edx
	pushl %ebx
	pushl %esi
	pushl %edi
	pushl %eax
	call	EXT_C(do_invalid_tss)
	addl	$4, %esp
	popl %edi
	popl %esi
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax
	iret
/* отсутствие сегмента */
ENTRY(segment_not_present):
	xchgl   (%esp), %eax
    pushl %ecx
	pushl %edx
	pushl %ebx
	pushl %esi
	pushl %edi
	pushl %eax
	call	EXT_C(do_segment_not_present)
	addl $4, %esp
	popl %edi
	popl %esi
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax
	iret
/* выход за пределы стека или отсутствие стека */
ENTRY(stack_fault_exception):
	xchgl   (%esp), %eax
    pushl %ecx
	pushl %edx
	pushl %ebx
	pushl %esi
	pushl %edi
	pushl %eax
	call	EXT_C(do_stack_fault_exception)
	addl $4, %esp
	popl %edi
	popl %esi
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax
	iret
/* нарушение обшей защиты */
ENTRY(general_protection_exception):
	xchgl   (%esp), %eax
    pushl %ecx
	pushl %edx
	pushl %ebx
	pushl %esi
	pushl %edi
	pushl %eax
	call	EXT_C(do_general_protection_exception)
	addl $4, %esp
	popl %edi
	popl %esi
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax
	iret
/* отсутствие страницы памяти */
ENTRY(page_fault_exception):
	xchgl   (%esp), %eax
    pushl %ecx
	pushl %edx
	pushl %ebx
	pushl %esi
	pushl %edi
	pushl %eax
	call	EXT_C(do_page_fault_exception)
	addl $4, %esp
	popl %edi
	popl %esi
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax
	iret
/* ошибка сопроцессора */
ENTRY(fpu_error):
	pushl %eax
	pushl %ecx
	pushl %edx
	pushl %ebx
	pushl %esi
	pushl %edi
	call	EXT_C(do_fpu_error)
	popl %edi
	popl %esi
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax
	iret
/* ошибка выравнивания */
ENTRY(alignment_check_exception):
	xchgl   (%esp), %eax
    pushl %ecx
	pushl %edx
	pushl %ebx
	pushl %esi
	pushl %edi
	pushl %eax
	call	EXT_C(do_alignment_check_exception)
	addl $4, %esp
	popl %edi
	popl %esi
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax
	iret
ENTRY(machine_check_exception):
	pushl %eax
	pushl %ecx
	pushl %edx
	pushl %ebx
	pushl %esi
	pushl %edi
	call	EXT_C(do_machine_check_exception)
	popl %edi
	popl %esi
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax
	iret
ENTRY(simd_floating_point_exception):
	pushl %eax
	pushl %ecx
	pushl %edx
	pushl %ebx
	pushl %esi
	pushl %edi
	call	EXT_C(do_simd_floating_point_exception)
	popl %edi
	popl %esi
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax
	iret
/* зарезервированные прерывания */
ENTRY(reserved_exception):
	pushl %eax
	pushl %ecx
	pushl %edx
	pushl %ebx
	pushl %esi
	pushl %edi
	call	EXT_C(do_reserved_exception)
	popl %edi
	popl %esi
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax
	iret
/* точки входа IRQ */
ENTRY(irq0):
	pushal
	movl	$0, %eax
	jmp	irq_code

ENTRY(irq1):
	pushal
	movl	$1, %eax
	jmp	irq_code

ENTRY(irq2):
	pushal
	movl	$2, %eax
	jmp	irq_code

ENTRY(irq3):
	pushal
	movl	$3, %eax
	jmp	irq_code

ENTRY(irq4):
	pushal
	movl	$4, %eax
	jmp	irq_code

ENTRY(irq5):
	pushal
	movl	$5, %eax
	jmp	irq_code

ENTRY(irq6):
	pushal
	movl	$6, %eax
	jmp	irq_code

ENTRY(irq7):
	pushal
	movl	$7, %eax
	jmp	irq_code

ENTRY(irq8):
	pushal
	movl	$8, %eax
	jmp	irq_code

ENTRY(irq9):
	pushal
	movl	$9, %eax
	jmp	irq_code

ENTRY(irq10):
	pushal
	movl	$10, %eax
	jmp	irq_code

ENTRY(irq11):
	pushal
	movl	$11, %eax
	jmp	irq_code

ENTRY(irq12):
	pushal
	movl	$12, %eax
	jmp	irq_code

ENTRY(irq13):
	pushal
	movl	$13, %eax
	jmp	irq_code

ENTRY(irq14):
	pushal
	movl	$14, %eax
	jmp	irq_code

ENTRY(irq15):
	pushal
	movl	$15, %eax
/*	jmp	irq_code
*/
irq_code:
	movl	$KERNEL_DS, %edx
	movw	%dx, %ds
	movw	%dx, %es
	pushl   %eax
	call	*EXT_C(table_irq)(,%eax,4)
	add     $4, %esp
	movl	$USER_DS, %edx
	movw	%dx, %ds
	movw	%dx, %es
	popal
	iret
/* Таблица системных вызовов */
.balign 4	/* выравниваем на 4 байт */
ENTRY(table_sys_call):
	.long	EXT_C(test_sys_call)

/* Таблица обработчиков IRQ */
ENTRY(table_irq):
	.long	EXT_C(default_handler_irq)	/* irq 0 */
	.long	EXT_C(default_handler_irq)	/* irq 1 */
	.long	EXT_C(default_handler_irq)	/* irq 2 */
	.long	EXT_C(default_handler_irq)	/* irq 3 */
	.long	EXT_C(default_handler_irq)	/* irq 4 */
	.long	EXT_C(default_handler_irq)	/* irq 5 */
	.long	EXT_C(default_handler_irq)	/* irq 6 */
	.long	EXT_C(default_handler_irq)	/* irq 7 */
	.long	EXT_C(default_handler_irq)	/* irq 8 */
	.long	EXT_C(default_handler_irq)	/* irq 9 */
	.long	EXT_C(default_handler_irq)	/* irq 10 */
	.long	EXT_C(default_handler_irq)	/* irq 11 */
	.long	EXT_C(default_handler_irq)	/* irq 12 */
	.long	EXT_C(default_handler_irq)	/* irq 13 */
	.long	EXT_C(default_handler_irq)	/* irq 14 */
	.long	EXT_C(default_handler_irq)	/* irq 15 */

