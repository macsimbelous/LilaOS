/* Copyright (C) 2004 Белоус Максим Юрьевич. */
#ifndef _INTS_H
#define _INTS_H
void set_desc_idt(unsigned char number, unsigned short selector, void *handler, unsigned char pl, unsigned char type);
#define enable_ints() asm("sti\n")
#define disable_ints() asm("cli\n")
void init_ints();

#endif /* _INTS_H */

