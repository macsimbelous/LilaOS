/* Copyright (C) 2004 Белоус Максим Юрьевич. */
#ifndef _IO_H
#define _IO_H

/* Функции работы с портами ввода/вывода */

static __inline__ void outb(unsigned short port, unsigned char value){
  asm("outb %0, %1":: "a"(value), "d"(port));
}

static __inline__ char inb(unsigned short port){
  unsigned char value;
  asm("inb %1, %0": "=a"(value): "d"(port));
  return value;
}

static __inline__ void outw(unsigned short port, unsigned short value){
  asm("outw %0, %1":: "a"(value), "d"(port));
}

static __inline__ unsigned short inw(unsigned short port){
  unsigned short value;
  asm("inw %1, %0": "=a"(value): "d"(port));
  return value;
}

static __inline__ void outl(unsigned short port, unsigned int value){
  asm("outl %0, %1":: "a"(value), "d"(port));
}

static __inline__ unsigned int inl(unsigned short port){
  unsigned int value;
  asm("inl %1, %0": "=a"(value): "d"(port));
  return value;
}

static __inline__ void outb_p(unsigned short port, unsigned char value){
  asm("outb %0, %1\njmp 1f\n1:\njmp 2f\n2:":: "a"(value), "d"(port));
}

static __inline__ void outw_p(unsigned short port, unsigned short value){
  asm("outw %0, %1\njmp 1f\n1:\njmp 2f\n2:":: "a"(value), "d"(port));
}

static __inline__ void outl_p(unsigned short port, unsigned int value){
  asm("outl %0, %1\njmp 1f\n1:\njmp 2f\n2:":: "a"(value), "d"(port));
}
#endif /* _IO_H */

