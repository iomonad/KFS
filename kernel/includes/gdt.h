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

#define GDT_SIZE 3

struct _kgdt_entry {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__ ((packed));

struct _kgdt_ptr {
	uint16_t limit;
	uint32_t base;
} __attribute__ ((packed));

struct _kgdt_entry gdt[GDT_SIZE];
struct _kgdt_ptr __gdt_ptr;

/*
 * Flush function that reload
 * our Segment registers.
 */
extern void gdt_commit(void);

/* Prototypes */

void install_system_gdt(void);

#endif	/* GDT_H */
