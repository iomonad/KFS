/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#include <gdt.h>
#include <kernel.h>

/* Global In memory GDT datastructure */
struct _kgdt_entry gdt[GDT_SIZE];
struct _kgdt_ptr _gdtptr;

/*
 * Add new descriptor to the table wo/ flush
 */
void kgdt_add_entry(uint8_t index, uint64_t base, uint64_t limit,
	            uint8_t access, uint8_t granularity)
{
	/* BASE ADDR SETUP */
	gdt[index].base_low = (base & 0xFFFF);
	gdt[index].base_middle = (base >> 16) & 0xFF;
	gdt[index].base_high = (base >> 24) & 0xFF;

	/* LIMIT SETUP */
	gdt[index].limit_low = (limit & 0xFFFF);
	gdt[index].granularity = ((limit >> 16) & 0x0F);

	/* GRANULARITY & ACCESS */
	gdt[index].granularity |= (granularity & 0xF0);
	gdt[index].access = access;
}

/*
 * GDT Setup
 */
void install_system_gdt(void)
{
	/*
	 * Initialize convenient structure
	 */
	_gdtptr.limit = (sizeof(struct _kgdt_entry) * GDT_SIZE) - 1;
	_gdtptr.base = (uint32_t)&gdt;

	/* Stick to standar guideline */
	kgdt_add_entry(0, 0, 0, 0, 0);

	_gdt_commit();
	return ;
}
