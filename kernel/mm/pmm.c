/* Copyright (C) 2004 Белоус Максим Юрьевич. */
#include <pmm.h>

#include <stdlib.h>
#include <ints.h>
#include <string.h>

#define MAX_ALLOC_PAGES 0xFFFE

#define PAGE_ALLOCATED 0xFFFF
#define PAGE_FREE 0x0000

static unsigned short *pages_map;
/* Количество физических страниц памяти. */
static unsigned int pages;
static unsigned int free_mem_pages;

/* Функция инициализирует менеджер физических страниц. */
void init_pmm(unsigned int size_memory, unsigned int start_memory, unsigned int low_memory){
	unsigned int i;
    if(((size_memory*1024)-start_memory)<((size_memory/4)*2)){
        printf("Not free memory\n");
        for(;;);
        }
    pages=size_memory/4;
    pages_map = (unsigned short *) PAGE_ALIGN(start_memory);
    start_memory = PAGE_ALIGN((unsigned int)(pages_map + pages));
	free_mem_pages = pages;
    memset(pages_map, 0x00, (pages*2));
	low_memory = low_memory / 4;

	pages_map[low_memory] = ((start_memory >> PAGE_SHIFT) - low_memory);
	for(i=low_memory+1; i<pages_map[low_memory]; i++){
		pages_map[i]=PAGE_ALLOCATED;
	}
	free_mem_pages = free_mem_pages - pages_map[low_memory];

	pages_map[0] = 1;
    printf("Init Physical Memory Manager\n");
    return;
    }

void free_pages(unsigned int address)
{
  int page, count, i;

  page = address >> PAGE_SHIFT;

  if(page > MAX_ALLOC_PAGES) {
    printf("free_pages failure: page > MAX_ALLOC_PAGES\n");
    for(;;);
  }

  if(!address & PAGE_MASK) {
    printf("free_pages failure: address not aligned\n");
    for(;;);
  }
	disable_ints();
  count = pages_map[page];
  
  if(count > MAX_ALLOC_PAGES) {
    printf("free_pages failure: count > MAX_ALLOC_PAGES\n");
    for(;;);
  }

  if((page + count) > pages){
	  printf("free_pages failure: page + count > pages\n");
	  for(;;);
  }
  for(i = 0; i < count; i++) {
    pages_map[page + i] = PAGE_FREE;
  }

  free_mem_pages += count;
  enable_ints();
}

unsigned int alloc_pages(int count)
{
  int i;
  int size_area;
  int start_area;

  if(count > MAX_ALLOC_PAGES) {
    printf("alloc_pages: count > MAX_ALLOC_PAGES\n");
	for(;;);
  }
  
  disable_ints();
  size_area = 0;

  for(i = 0; i < pages; i++) {
    if (pages_map[i] != PAGE_FREE) {
      size_area = 0;

    } else {
      size_area++;
      
      if(size_area == count) {
      
	start_area = i - size_area + 1;
	
	

	pages_map[start_area] = count;
	
	for(i = 1; i < count; i++) {
	  pages_map[start_area + i] = PAGE_ALLOCATED;
	}

	free_mem_pages -= count;
	enable_ints();
	return (unsigned int)(start_area << PAGE_SHIFT);
      }
    }
  }
  printf("Not Memory (requested %i pages)\n", count);
  for(;;);
}
unsigned int get_mem_info(int flag){
	if(flag == 0){
		return pages;
	}
	else {
		return free_mem_pages;
	}
}
