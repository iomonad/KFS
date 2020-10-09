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
#include <time.h>
#include <memory.h>
#include <stdlib.h>
#include <kernel.h>
#include <lifecycle.h>

/* Reference from linker file */
extern uint32_t physmemstart;

/* Memory referenced from linker value */
kheap_t served_address = (uint32_t)&physmemstart;

/* Cursor & Kernel directory pages */
page_directory_t *curr_dir_page = NULL;
page_directory_t *kernel_dir_page = NULL;

uint32_t frame_count;
uint32_t *frameptr = NULL;

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

/* Frame Algorithm */

/*
 * Set a bit in frame Bitset
 */
void bf_set(uint32_t faddr)
{
	uint32_t frame = faddr / 0x1000;

	uint32_t idx = INDEX_FROM_BIT(frame);

	uint32_t off = OFFSET_FROM_BIT(frame);

	frameptr[idx] |= (0x1 << off);
}

/*
 * Clear bit in frame Bitset
 */
void bf_clear(uint32_t faddr)
{
	uint32_t frame = faddr / 0x1000;

	uint32_t idx = INDEX_FROM_BIT(frame);

	uint32_t off = OFFSET_FROM_BIT(frame);

	frameptr[idx] &= ~(0x1 << off);
}

/*
 * Test if bit is set in Frame Bitset
 */
uint32_t bf_assert(uint32_t faddr)
{
	uint32_t frame = faddr / 0x1000;

	uint32_t idx = INDEX_FROM_BIT(frame);

	uint32_t off = OFFSET_FROM_BIT(frame);

	return (frameptr[idx] & (0x1 << off));
}

/*
 * Find the first free frame
 */
uint32_t bf_first_frame(void)
{
	for (uint32_t i = 0; i < INDEX_FROM_BIT(frame_count); i++) {
		/*
		 * If memory not free, skip
		 */
		if (frameptr[i] != 0xFFFFFFFF) {
			for (uint32_t j = 0; j < 32; j++) {
				uint32_t assert = 0x1 << j;

				if ((frameptr[i] & assert) != NULL) {
					return (i * 4 * 8) + j;
				}
			}
		}
	}
	return NULL;
}

void bf_alloc_frame(page_t *page, int is_kspace,
			   int is_writeable)
{
	if (page->frame != NULL) {
		/*
		 * Frame already allocated, exit.
		 * Maybe add debug w/ dmesg implementation in the
		 * future ?
		 */
		return ;
	}

	uint32_t idx = bf_first_frame();
	if (idx == 0xFFFFFFFF) {
		kpanic("No free frames availables !!");
	}

	/* Place ownership on frame */
	bf_set(idx * 0x1000);

	page->present = 1;
	page->rw = is_writeable;
	page->user = is_kspace;
	page->frame = idx;
}

void bf_dealloc_frame(page_t *page)
{
	uint32_t frame;

	if ((frame = page->frame) == NULL) {
		/*
		 * No associated page to free !
		 * Maybe log it to DMESG ?
		 */
		return ;
	}
	bf_clear(frame);
	page->frame = 0x0;
}

static void initialize_pagging(page_directory_t *dir)
{
	uint32_t cr0_reg;

	curr_dir_page = dir;

	asm volatile("mov %0, %%cr3":: "r"(&dir->physical_table));

	/*
	 * Note: setting the paging flag when the
	 * protection flag is clear causes a
	 * general-protection exception.
	 */
	asm volatile("mov %%cr0, %0": "=r"(cr0_reg));
	cr0_reg |= 0x80000001;
	cr0_reg = 0;
	asm volatile("mov %0, %%cr0":: "r"(cr0_reg));
}

static page_t *retrieve_page(uint32_t addr, int craft,
			     page_directory_t *dir)
{
	uint32_t tidx;		/* Our memory table index */

	/* Convert Addr to Index */
	addr /= 0x1000;
	tidx = addr / 0x400;

	if (dir->table[tidx] != NULL) {
		/*
		 * At thi point we know that the table is already
		 * assigned so simply return his reference.
		 */
		return &dir->table[tidx]->pages[addr % 0x400];
	}
	if (craft != 0) {
		/*
		 * In the case of the page is asked, not existing
		 * and user supplied the `craft` flag, we will alloc
		 * allignated & physical memory page table
		 */
		uint32_t physical_table;

		if ((dir->table[tidx] = (page_table_t*)__kmalloc_impl(sizeof(page_table_t), 1, &physical_table)) == NULL) {
			kpanic("Failed allocating page table !!");
		}
		if (physical_table == NULL) {
			kpanic("Physical Table Error !");
		}
		memset(dir->table[tidx], 0x0, 0x1000);
		dir->physical_table[tidx] = physical_table | 0x7; // (PRESENT | RW | US)
		return &dir->table[tidx]->pages[addr % 0x400];
	}
	return NULL;
}

/* Page fault interrupt callback */
static void page_fault_int(registers_t regs)
{
	uint32_t fault_addr = NULL;

	/* Fault addr are in CR2 Register */
	asm volatile("mov %%cr2, %0" : "=r" (fault_addr));

	vga_puts("Page fault !! Trace infos: (");
	if (!(regs.err_code & 0x1)) {
		vga_puts("PRESENT ");
	}
	if (regs.err_code & 0x2) {
		vga_puts("RONLY ");
	}
	if (regs.err_code & 0x4) {
		vga_puts("USER_MODE ");
	}
	if (regs.err_code & 0x8) {
		vga_puts("RESERVED");
	}
	if (regs.err_code & 0x10) {
		vga_puts("IFETCH");
	}
	vga_puts(") at ");
	vga_puthex(fault_addr);
	vga_endl();
	kpanic("Page Fault");
}

void __attribute__ ((cold))
install_system_memory(void)
{
	/* Physical memory Size */
	uint32_t memory_end_page = 0x1000000;

	frame_count = memory_end_page / 0x1000;

	/* Initialise Frame Pointer */
	if ((frameptr = (uint32_t*)kmalloc(INDEX_FROM_BIT(frame_count))) == NULL) {
		kpanic("Unable to alloc Frame Pointer !");
	}
	memset(frameptr, 0x0, INDEX_FROM_BIT(frame_count));

	/* Initialise Kernel Page Directory */
	if ((kernel_dir_page = (page_directory_t*)__kmalloc_impl(sizeof(page_directory_t), 1, NULL)) == NULL) {
		kpanic("Unable to alloc kernel directory page");
	}
	memset(kernel_dir_page, 0x0, sizeof(page_directory_t));

	/* The head of directory */
	curr_dir_page = kernel_dir_page;

	/*
	 * Allocate frames
	 */
	for (kheap_t i = 0; i < served_address; i += 0x1000) {
		/* TODO: Handle Userspace memory allocation */
		bf_alloc_frame(retrieve_page(i, 1, kernel_dir_page), 0, 0);
	}
	register_interrupt_callback(14, page_fault_int);
	return initialize_pagging(kernel_dir_page);
}
