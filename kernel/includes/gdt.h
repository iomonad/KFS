/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#ifndef GDT_H
#define GDT_H

#include <types.h>
#include <kernel.h>

#define GDT_SIZE 5

/*
 * Modelize an GDT entry
 */
struct _kgdt_entry {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__ ((packed));

/*
 * Modelize a pointer that implement
 * an limit wich basically is the max
 * bytes taken up by the GDT-1.
 */
struct _kgdt_ptr {
	uint16_t limit;
	uint32_t base;
} __attribute__ ((packed));

/*
 * Flush function that reload
 * our Segment registers.
 */
extern void _gdt_commit(void);

/* Prototypes */

void install_system_gdt(void);
void kgdt_add_entry(uint8_t index, uint64_t base, uint64_t limit,
	            uint8_t access, uint8_t granularity);

#endif	/* GDT_H */
