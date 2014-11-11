/* Copyright (C) 2004 Белоус Максим Юрьевич. */
#ifndef _CONFIG_H
#define _CONFIG_H

#define ALIGN .align 16,0x90

# define EXT_C(sym)			_ ## sym

#define ENTRY(sym) \
  .globl EXT_C(sym); \
  ALIGN; \
  EXT_C(sym)

#endif
