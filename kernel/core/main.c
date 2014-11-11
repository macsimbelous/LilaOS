/* Copyright (C) 2003 Белоус Максим Юрьевич. */
#include <multiboot.h>
#include <version.h>
#include <pmm.h>
#include <stdlib.h>
#include <ints.h>
#include <cmd.h>
#include <heap.h>

void init_video();
void init_irq();
void init_timer();
void init_rd(void * address);

void start_kernel(unsigned long magic, mbi_t *boot_info, unsigned long end_bss){
    parse_options((char *)boot_info->cmd);
    init_video();
    printf(KERNEL_VERSION_STRING);
    printf("\nCopyright (C) 2004 Maxim Belous\n");
    printf("Command Line: %s\n", (char *)boot_info->cmd);
    init_ints();
    init_irq();
    enable_ints();
    printf("Enable Interrupts\n");
    init_pmm(boot_info->mem_high+1024, end_bss, boot_info->mem_low);
    printf("Install Memory %uM\n", (boot_info->mem_high+1024)/1024);
    init_heap();
    init_timer();
    for(;;);
    return;
    }

