/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#include <vga.h>
#include <memory.h>
#include <kernel.h>

/* Reference from linker file */
extern uint32_t physmemstart;

/* Memory referenced from linker value */
kheap_t served_address = (uint32_t)&physmemstart;

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

/*  */
void __attribute__ ((cold))
install_system_memory(void)
{
	return ;
}
