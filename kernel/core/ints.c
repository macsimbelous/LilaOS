/* Copyright (C) 2003 Белоус Максим Юрьевич. */
#include <config.h>
#include <descriptor.h>
#include <string.h>
#include <segments.h>
#include <stdlib.h>

void divide_error_exception();
void debug_exception();
void nmi();
void breakpoint_exception();
void overflow_exception();
void bound_range_exceeded_exception();
void invalid_opcode_exception();
void no_math();
void double_fault_exception();
void coprocessor_segment_overrun();
void invalid_tss();
void segment_not_present();
void stack_fault_exception();
void general_protection_exception();
void page_fault_exception();
void reserved_exception();
void fpu_error();
void alignment_check_exception();
void machine_check_exception();
void simd_floating_point_exception();
void sys_call();

/* Таблица IDT */
static desc_idt_t idt[256];

/* Устанавливает дескриптор IDT. */
void set_desc_idt(unsigned char number, unsigned short selector, void *handler, unsigned char pl, unsigned char type){
  desc_idt_t temp_desc;

  temp_desc.offset_low = (unsigned int) handler & 0xFFFF;
  temp_desc.offset_high = ((unsigned int) handler >> 16) & 0xFFFF;
  temp_desc.selector = selector;
  temp_desc.type_dpl = (0x80 | (pl << 5) | (type & 0x1F));
  temp_desc.reserved = 0;

  memcpy(&idt[number], (void *) &temp_desc, 8);
	}

void init_ints(){
    unsigned int idtr[2];
    idtr[0] = (256*8-1) << 16;
    idtr[1] = (unsigned int) &idt;
    asm volatile ("lidt (%0)"::"r"(((char *) idtr)+2));
    /* Устанавливаем дескрипторы IDT */
    set_desc_idt(0, KERNEL_CS, divide_error_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(1, KERNEL_CS, debug_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(2, KERNEL_CS, nmi, 0, INTERRUPT_GATE_32);
    set_desc_idt(3, KERNEL_CS, breakpoint_exception, 0, TRAP_GATE_32);
    set_desc_idt(4, KERNEL_CS, overflow_exception, 0, TRAP_GATE_32);
    set_desc_idt(5, KERNEL_CS, bound_range_exceeded_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(6, KERNEL_CS, invalid_opcode_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(7, KERNEL_CS, no_math, 0, INTERRUPT_GATE_32);
    set_desc_idt(8, KERNEL_CS, double_fault_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(9, KERNEL_CS, coprocessor_segment_overrun, 0, INTERRUPT_GATE_32);
    set_desc_idt(10, KERNEL_CS, invalid_tss, 0, INTERRUPT_GATE_32);
    set_desc_idt(11, KERNEL_CS, segment_not_present, 0, INTERRUPT_GATE_32);
    set_desc_idt(12, KERNEL_CS, stack_fault_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(13, KERNEL_CS, general_protection_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(14, KERNEL_CS, page_fault_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(15, KERNEL_CS, reserved_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(16, KERNEL_CS, fpu_error, 0, INTERRUPT_GATE_32);
    set_desc_idt(17, KERNEL_CS, alignment_check_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(18, KERNEL_CS, machine_check_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(19, KERNEL_CS, simd_floating_point_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(20, KERNEL_CS, reserved_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(21, KERNEL_CS, reserved_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(22, KERNEL_CS, reserved_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(23, KERNEL_CS, reserved_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(24, KERNEL_CS, reserved_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(25, KERNEL_CS, reserved_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(26, KERNEL_CS, reserved_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(27, KERNEL_CS, reserved_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(28, KERNEL_CS, reserved_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(29, KERNEL_CS, reserved_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(30, KERNEL_CS, reserved_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(31, KERNEL_CS, reserved_exception, 0, INTERRUPT_GATE_32);
    set_desc_idt(255, KERNEL_CS, sys_call, 0, TRAP_GATE_32);
    printf("Init Interrupts\n");
    return;
    }


