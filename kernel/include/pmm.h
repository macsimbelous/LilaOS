/* Copyright (C) 2004 Белоус Максим Юрьевич. */
#ifndef _PMM_H_
#define _PMM_H_

#define PAGE_SHIFT			12
#define PAGE_SIZE			(1UL << PAGE_SHIFT)
#define PAGE_MASK			(~(PAGE_SIZE-1))
#define PAGE_ALIGN(addr)		(((addr)+PAGE_SIZE-1)&PAGE_MASK)
unsigned int alloc_pages(int count);
void free_pages(unsigned int address);
unsigned int get_mem_info(int flag);
void init_pmm(unsigned int size_memory, unsigned int start_memory, unsigned int low_memory);

#endif /* _PMM_H_ */

