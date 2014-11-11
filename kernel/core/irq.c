/* Copyright (C) 2003 Белоус Максим Юрьевич. */
#include <config.h>
#include <descriptor.h>
#include <segments.h>
#include <io.h>
#include <stdlib.h>
#include <ints.h>
void default_handler_irq(int number);
void irq0();
void irq1();
void irq2();
void irq3();
void irq4();
void irq5();
void irq6();
void irq7();
void irq8();
void irq9();
void irq10();
void irq11();
void irq12();
void irq13();
void irq14();
void irq15();
extern unsigned int table_irq[];

void init_irq(){
    /* Инициализируем ведущий контроллер прерываний */ 
    outb_p(0x20, 0x11);
    outb_p(0x21, 32);
    outb_p(0x21, 0x04);
    outb_p(0x21, 0x0D);
    outb_p(0x21, 0xFF);
    /* Инициализируем ведомый контроллер прерываний */
    outb_p(0xA0, 0x11);
    outb_p(0xA1, 40);
    outb_p(0xA1, 0x02);
    outb_p(0xA1, 0x09);
    outb(0xA1, 0xFF);
    /* Устанавливаем прерывания */
    set_desc_idt(32, KERNEL_CS, irq0, 0, INTERRUPT_GATE_32);
    set_desc_idt(33, KERNEL_CS, irq1, 0, INTERRUPT_GATE_32);
    set_desc_idt(34, KERNEL_CS, irq2, 0, INTERRUPT_GATE_32);
    set_desc_idt(35, KERNEL_CS, irq3, 0, INTERRUPT_GATE_32);
    set_desc_idt(36, KERNEL_CS, irq4, 0, INTERRUPT_GATE_32);
    set_desc_idt(37, KERNEL_CS, irq5, 0, INTERRUPT_GATE_32);
    set_desc_idt(38, KERNEL_CS, irq6, 0, INTERRUPT_GATE_32);
    set_desc_idt(39, KERNEL_CS, irq7, 0, INTERRUPT_GATE_32);
    set_desc_idt(40, KERNEL_CS, irq8, 0, INTERRUPT_GATE_32);
    set_desc_idt(41, KERNEL_CS, irq9, 0, INTERRUPT_GATE_32);
    set_desc_idt(42, KERNEL_CS, irq10, 0, INTERRUPT_GATE_32);
    set_desc_idt(43, KERNEL_CS, irq11, 0, INTERRUPT_GATE_32);
    set_desc_idt(44, KERNEL_CS, irq12, 0, INTERRUPT_GATE_32);
    set_desc_idt(45, KERNEL_CS, irq13, 0, INTERRUPT_GATE_32);
    set_desc_idt(46, KERNEL_CS, irq14, 0, INTERRUPT_GATE_32);
    set_desc_idt(47, KERNEL_CS, irq15, 0, INTERRUPT_GATE_32);
    printf("Init IRQ\n");
    return;
}
int set_handler_irq(void *handler, unsigned char number){
    if(number>=16)
        return 1;
    if(table_irq[number]!=(unsigned int)default_handler_irq)
        return 2;
    table_irq[number]=(unsigned int)handler;
    if(number>=8){
        outb(0xa1, (inb(0xa1) & ((1 << (number-8)) ^ 0xFF)));
    }
    else{
        outb(0x21, (inb(0x21) & ((1 << number) ^ 0xFF)));
    }
    return 0;
}
int unset_handler_irq(unsigned char number){
    if(number>=16)
        return 1;
    table_irq[number]=(unsigned int)default_handler_irq;
    if(number>=8){
        outb(0xa1, (inb(0xa1) | (1 << number)));
    }
    else{
        outb(0x21, (inb(0x21) | (1 << number)));
    }
    return 0;
}
void default_handler_irq(int number){
    printf("Default Handler IRQ %u\n", number);
    if(number<8)
        outb(0x20, 0x20);
    else
        outb(0xA0, 0x20);
    return;
    }

