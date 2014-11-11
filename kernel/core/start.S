/* Ядро ОС */
/* start.S - здесь начинается выполнение ядра */
/* Copyright (C) 2002 Белоус Максим Юрьевич */
#define ASM	1
#include <config.h>
#include <multiboot.h>

	.text
	.globl	start, _start, _mainCRTStartup
	.extern	EXT_C(start_kernel)
start:
_start:
_mainCRTStartup:
	jmp	entry

	/* выравниваем на четыре байта  */
	.balign	4
	
	/* Multiboot заголовок */
multiboot_header:
	/* магическое число */
	.long	MULTIBOOT_HEADER_MAGIC
	/* флаги */
	.long	MULTIBOOT_HEADER_FLAGS
	/* контрольная сумма */
	.long	-(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
	/* адрес заголовка */
	.long	multiboot_header
	/* адрес загрузки */
	.long	_start
	/* адрес канца секции данных */
	.long	__data_end__
	/* адрес конца секции не инициальзированных данных */
	.long	__bss_end__
	/* адрес точки входа */
	.long	entry
entry:
	/* устанавливаем GDT */
	lgdt	gdt_regs
	/* сбрасываем конвеер */
	jmp	$0x8,$jumps
jumps:
	/* устанавливаем регистры */
	movw	$0x10, %dx
	movw	%dx, %ds
	movw	%dx, %es
	movw	%dx, %fs
	movw	%dx, %gs
	movw	%dx, %ss
	/* инициализируем esp  */
	movl	$stack+16384, %esp
	/* сбрасываем EFLAGS.  */
	pushl	$0
	popf

	/* ложим в стек указатель на структуру с multiboot информацией, магическое число и адрес конца секции ненициализированных данных */
	pushl	$__bss_end__
	pushl	%ebx
	pushl	%eax
	call	EXT_C(start_kernel)

	/* бесконечный цикл на случай выхода из функции startkernel */
loop:	jmp	loop
	/* начальный стек ядра */
	.balign	4
stack:
	.fill 16384,1,0
	/* значения для регистра GDTR */
gdt_regs:
	.word	6*8-1
	.long	EXT_C(gdt)

	/* GDT */
	.balign	16
ENTRY(gdt):
	.quad 0x0000000000000000	/* нулевой дескриптор 0x00*/
	.quad 0x00cf9a000000ffff	/* дескриптор кода ядра 0x08 */
	.quad 0x00cf92000000ffff	/* дескриптор данных ядра 0x10 */
	.quad 0x00cffa000000ffff	/* дескриптор кода пользователя 0x1b */
	.quad 0x00cff2000000ffff	/* дескриптор данных пользователя 0x23 */
