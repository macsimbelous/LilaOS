/* Copyright (C) 2003 Белоус Максим Юрьевич. */
#ifndef _DESCRIPTOR_H
#define _DESCRIPTOR_H

enum
{
  TASK_GATE_32 = 5,
  TSS = 9,
  CALL_GATE = 12,
  INTERRUPT_GATE_32 = 14,
  TRAP_GATE_32 = 15,
};

typedef struct
{
  unsigned short limit_low;
  unsigned short base_low;
  unsigned char base_high;
  unsigned char type_dpl;
  unsigned char limit_high;
  unsigned char base_high2;
}desc_gdt_t;

typedef struct
{
  unsigned short offset_low;
  unsigned short selector;
  unsigned char reserved;
  unsigned char type_dpl;                 
  unsigned short offset_high;
} desc_idt_t;

#endif /* !DESCRIPTOR_H */
