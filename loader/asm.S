

#define ASM_FILE

#include "shared.h"

	.text
	.code16
	.org 0x0, 0x0
	.globl	start, _start, _mainCRTStartup
start:
_start:
_mainCRTStartup:
/* Стартовый код реального режима. */
	cli
	/* Устанавливаем сегментные регистры. */
	xorw	%ax, %ax
	movw	%ax, %ds
	movw	%ax, %ss
	movw	%ax, %es

	/* Устанавливаем стек реального режима. */
	movl	$REALSTACK, %ebp
	movl	%ebp, %esp

	/* Переходим в защищённый режим. */

	/* load the GDT register */
	DATA32	ADDR32	lgdt	gdtdesc

	/* turn on protected mode */
	movl	%cr0, %eax
	orl	$CR0_PE_ON, %eax
	movl	%eax, %cr0

	/* jump to relocation, flush prefetch queue, and reload %cs */
	DATA32	ljmp	$PROT_MODE_CSEG, $protcseg
	.code32
protcseg:

	/* reload other segment registers */
	movw	$PROT_MODE_DSEG, %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %fs
	movw	%ax, %gs
	movw	%ax, %ss

	/* get protected mode stack */
	movl	protstack, %eax
	movl	%eax, %esp

	xorl	%eax, %eax
	/* Стартовый код защищённова режима. */
	.code32

	/* Переходим к коду на Си. */
	call EXT_C(start_loader)

/*
 * reboot()
 *
 * Перезагрузка.
 */
ENTRY(reboot)
	/* save the protected mode stack */
	movl	%esp, %eax
	movl	%eax, protstack

	/* set up new stack */
	movl	$REALSTACK, %eax
	movl	%eax, %esp

	/* set up segment limits */
	movw	$PSEUDO_RM_DSEG, %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %fs
	movw	%ax, %gs
	movw	%ax, %ss

	/* this might be an extra step */
	ljmp	$PSEUDO_RM_CSEG, $tmpcseg	/* jump to a 16 bit segment */

tmpcseg:
	.code16

	/* clear the PE bit of CR0 */
	movl	%cr0, %eax
	andl 	$CR0_PE_OFF, %eax
	movl	%eax, %cr0

	/* flush prefetch queue, reload %cs */
	DATA32	ljmp	$0, $realcseg

realcseg:

	xorl	%eax, %eax

	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %fs
	movw	%ax, %gs
	movw	%ax, %ss

	/* restore interrupts */
	sti

	/* cold boot */
	movw	$0x0472, %di
	movw	%ax, (%di)
	ljmp	$0xFFFF, $0x0000

/* get_code_end() :  return the address of the end of the code
 * This is here so that it can be replaced by asmstub.c.
 */
    .code32
ENTRY(get_code_end)
	/* возвращает конец секции данных */
	movl	$_end, %eax
	shrl	$2, %eax
	incl	%eax
	shll	$2, %eax
	ret

/* Функция выводит посредствам BIOS один символ на экран */
ENTRY(low_put_char)
    pushl   %ebp
    movl    %esp, %ebp
    pushal
    
    movl    8(%ebp), %eax
    movl    %eax, param    

	/* save the protected mode stack */
	movl	%esp, %eax
	movl	%eax, protstack

	/* set up new stack */
	movl	$REALSTACK, %eax
	movl	%eax, %esp

	/* set up segment limits */
	movw	$PSEUDO_RM_DSEG, %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %fs
	movw	%ax, %gs
	movw	%ax, %ss

	/* this might be an extra step */
	ljmp	$PSEUDO_RM_CSEG, $low_put_char_tmpcseg	/* jump to a 16 bit segment */

low_put_char_tmpcseg:
	.code16

	/* clear the PE bit of CR0 */
	movl	%cr0, %eax
	andl 	$CR0_PE_OFF, %eax
	movl	%eax, %cr0

	/* flush prefetch queue, reload %cs */
	DATA32	ljmp	$0, $low_put_char_realcseg

low_put_char_realcseg:

	xorl	%eax, %eax

	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %fs
	movw	%ax, %gs
	movw	%ax, %ss

	/* restore interrupts */
	sti

	movl    param, %eax

    movb    $0x0E, %ah
    movw    $0x0007, %bx
    int    $0x10

/* Переходим в защищённый режим. */
    cli
	/* load the GDT register */
	DATA32	ADDR32	lgdt	gdtdesc

	/* turn on protected mode */
	movl	%cr0, %eax
	orl	$CR0_PE_ON, %eax
	movl	%eax, %cr0

	/* jump to relocation, flush prefetch queue, and reload %cs */
	DATA32	ljmp	$PROT_MODE_CSEG, $low_put_char_protcseg
	.code32
low_put_char_protcseg:

	/* reload other segment registers */
	movw	$PROT_MODE_DSEG, %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %fs
	movw	%ax, %gs
	movw	%ax, %ss

	/* get protected mode stack */
	movl	protstack, %eax
	movl	%eax, %esp

    popal
    popl    %ebp
    addl    $4, %esp
    ret
    
/*
 *  This is the area for all of the special variables.
 */

	.p2align	2	/* force 4-byte alignment */

protstack:
	.long	0x7c00
param:
    .long 0x0

/*
 * This is the Global Descriptor Table
 *
 *  An entry, a "Segment Descriptor", looks like this:
 *
 * 31          24         19   16                 7           0
 * ------------------------------------------------------------
 * |             | |B| |A|       | |   |1|0|E|W|A|            |
 * | BASE 31..24 |G|/|0|V| LIMIT |P|DPL|  TYPE   | BASE 23:16 |
 * |             | |D| |L| 19..16| |   |1|1|C|R|A|            |
 * ------------------------------------------------------------
 * |                             |                            |
 * |        BASE 15..0           |       LIMIT 15..0          |
 * |                             |                            |
 * ------------------------------------------------------------
 *
 *  Note the ordering of the data items is reversed from the above
 *  description.
 */

	.p2align	2	/* force 4-byte alignment */
gdt:
	.word	0, 0
	.byte	0, 0, 0, 0

	/* code segment */
	.word	0xFFFF, 0
	.byte	0, 0x9A, 0xCF, 0

	/* data segment */
	.word	0xFFFF, 0
	.byte	0, 0x92, 0xCF, 0

	/* 16 bit real mode CS */
	.word	0xFFFF, 0
	.byte	0, 0x9E, 0, 0

	/* 16 bit real mode DS */
	.word	0xFFFF, 0
	.byte	0, 0x92, 0, 0


/* this is the GDT descriptor */
gdtdesc:
	.word	0x27			/* limit */
	.long	gdt			/* addr */
