/* ���� �� */
/* start.S - ����� ���������� ���������� ���� */
/* Copyright (C) 2002 ������ ������ ������� */
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

	/* ����������� �� ������ �����  */
	.balign	4
	
	/* Multiboot ��������� */
multiboot_header:
	/* ���������� ����� */
	.long	MULTIBOOT_HEADER_MAGIC
	/* ����� */
	.long	MULTIBOOT_HEADER_FLAGS
	/* ����������� ����� */
	.long	-(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
	/* ����� ��������� */
	.long	multiboot_header
	/* ����� �������� */
	.long	_start
	/* ����� ����� ������ ������ */
	.long	__data_end__
	/* ����� ����� ������ �� ������������������ ������ */
	.long	__bss_end__
	/* ����� ����� ����� */
	.long	entry
entry:
	/* ������������� GDT */
	lgdt	gdt_regs
	/* ���������� ������� */
	jmp	$0x8,$jumps
jumps:
	/* ������������� �������� */
	movw	$0x10, %dx
	movw	%dx, %ds
	movw	%dx, %es
	movw	%dx, %fs
	movw	%dx, %gs
	movw	%dx, %ss
	/* �������������� esp  */
	movl	$stack+16384, %esp
	/* ���������� EFLAGS.  */
	pushl	$0
	popf

	/* ����� � ���� ��������� �� ��������� � multiboot �����������, ���������� ����� � ����� ����� ������ ������������������� ������ */
	pushl	$__bss_end__
	pushl	%ebx
	pushl	%eax
	call	EXT_C(start_kernel)

	/* ����������� ���� �� ������ ������ �� ������� startkernel */
loop:	jmp	loop
	/* ��������� ���� ���� */
	.balign	4
stack:
	.fill 16384,1,0
	/* �������� ��� �������� GDTR */
gdt_regs:
	.word	6*8-1
	.long	EXT_C(gdt)

	/* GDT */
	.balign	16
ENTRY(gdt):
	.quad 0x0000000000000000	/* ������� ���������� 0x00*/
	.quad 0x00cf9a000000ffff	/* ���������� ���� ���� 0x08 */
	.quad 0x00cf92000000ffff	/* ���������� ������ ���� 0x10 */
	.quad 0x00cffa000000ffff	/* ���������� ���� ������������ 0x1b */
	.quad 0x00cff2000000ffff	/* ���������� ������ ������������ 0x23 */
