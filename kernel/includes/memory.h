/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#ifndef MEMORY_H
#define MEMORY_H

#include <types.h>

#define PAGE_TABLE_SIZE 1024

/*
 * Structure that modelize a
 * memory page.
 * See:
 *  - https://wiki.osdev.org/Paging
 */
typedef struct page {
	uint32_t present :1;	/* Page is present in memory */
	uint32_t rw      :1;	/* Readonly if clear - RW if set */
	uint32_t user    :1;	/* HW level if clear */
	uint32_t access  :1;	/* Accessed since last page refresh ? */
	uint32_t dirty   :1;	/* Written since last refresh ? */
	uint32_t unused  :7;	/* Reserved bits */
	uint32_t frame   :20;	/* Frame Adress left shifted of 12bits */
} page_t;

/*
 * Our page table
 */
typedef struct page_table {
	page_t pages[PAGE_TABLE_SIZE];
} page_table_t;

/*
 * Structure that modelize
 * a page directory
 * See:
 *  - https://wiki.osdev.org/Paging
 */
typedef struct page_directory {
	/*
	 * Pointer to the current page table
	 */
	page_table_t *table[PAGE_TABLE_SIZE];

	/*
	 * Physical table translation.
	 * Used to load it into CR3 Register
	 * according x86
	 */
	uint32_t physical_table[PAGE_TABLE_SIZE];

	/*
	 * Physical addr of translation
	 * table
	 */
	uint32_t physical_table_addr;
} page_directory_t;

/*
 * An tiny typedef to make code
 * readability better
 */
typedef uint32_t kheap_t;

/* PROTOTYPES */

void __attribute__ ((cold)) install_system_memory(void);

uint32_t kmalloc(const uint32_t size);
uint32_t kpmalloc(const uint32_t size, uint32_t *phyref);

#endif	/* MEMORY_H */
