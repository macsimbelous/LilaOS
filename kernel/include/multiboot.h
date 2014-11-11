/* Copyright (C) 2003 Белоус Максим Юрьевич. */

/* Магическое число Multiboot заголовка.  */
#define MULTIBOOT_HEADER_MAGIC		0x1BADB002
#ifndef _MULTIBOOT_H
#define _MULTIBOOT_H
/* Флаги Multiboot заголовка. */
# define MULTIBOOT_HEADER_FLAGS		0x00010002

/* Магический номер Multiboot-совместимого загрузчика. */
#define MULTIBOOT_BOOTLOADER_MAGIC	0x2BADB002

#ifndef ASM

/* Multiboot заголовок. */
typedef struct mbh{
  unsigned long magic;
  unsigned long flags;
  unsigned long checksum;
  unsigned long header_addr;
  unsigned long load_addr;
  unsigned long load_end_addr;
  unsigned long bss_end_addr;
  unsigned long entry_addr;
}mbh_t;

/* Multiboot информация. */
typedef struct mbi{
  unsigned long flags;
  unsigned long mem_low;
  unsigned long mem_high;
  unsigned long boot_dev;
  unsigned long cmd;
  unsigned long mod_count;
  unsigned long mod_addres;
}mbi_t;

/* Структура модулей */
typedef struct mbi_mod{
  unsigned long start;
  unsigned long end;
  unsigned long string;
  unsigned long reserved;
}mbi_mod_t;

/* Карта памяти. */
typedef struct mbi_mem_map{
  unsigned long Size;
  unsigned long BaseAddresLow;
  unsigned long BaseAddresHigh;
  unsigned long LengthLow;
  unsigned long LengthHigh;
  unsigned long Type;
}mbi_mem_map_t;

#endif /* ! ASM */
#endif
