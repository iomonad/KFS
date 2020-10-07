/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#include <vga.h>
#include <irq.h>
#include <memory.h>
#include <kernel.h>
#include <lifecycle.h>

/* Reference from linker file */
extern uint32_t physmemstart;

/* Memory referenced from linker value */
kheap_t served_address = (uint32_t)&physmemstart;

/* Cursor & Kernel directory pages */
page_directory_t *curr_dir_page = NULL;
page_directory_t *kernel_dir_page = NULL;

/*
 * Kernel memory implementation management, with allignement
 * support.
 */
static uint32_t __kmalloc_impl(const uint32_t size, int alignement,
		 uint32_t *phys_ref)
{
	uint32_t ptr = served_address;

	/* If not already alignated */
	if (alignement == 1 && (served_address & 0xFFFFF000)) {
		served_address &= 0xFFFFF000;
		served_address += 0x1000;
	}
	/* Push physical reference */
	if (phys_ref) {
		*phys_ref = served_address;
	}
	served_address += size;
	return ptr;
}

/*
 * Primary implementation, correctly
 * alignated & no physical address
 */
uint32_t kmalloc(const uint32_t size)
{
	return __kmalloc_impl(size, 1, NULL);
}

/*
 * Primary implementation, correctly
 * alignated & assoc physical address
 */
uint32_t kpmalloc(const uint32_t size, uint32_t *phyref)
{
	return __kmalloc_impl(size, 1, phyref);
}

/* Bitset algorithms implementation */


static void initialize_pagging(page_directory_t *dir)
{
	uint32_t cr0_reg;

	curr_dir_page = dir;
	asm volatile("mov %0, %%cr3":: "r"(&dir->physical_table));
	asm volatile("mov %%cr0, %0": "=r"(cr0_reg));
	cr0_reg |= 0x80000000; 	/* This enable paging according x86 */
	asm volatile("mov %0, %%cr0":: "r"(cr0_reg));
}

/* Page fault interrupt callback */
static void page_fault_int(registers_t r)
{
	(void)r;
	/* TODO: Need debug address print */
	kpanic("Page Fault");
}

void __attribute__ ((cold))
install_system_memory(void)
{
	/* Physical memory Size */
	//uint32_t memory_end_page = 0x1000000;

	register_interrupt_callback(14, page_fault_int);
	return initialize_pagging(kernel_dir_page); /*  */
}
