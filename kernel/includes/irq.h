/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#ifndef IRQ_H
#define IRQ_H

#include <types.h>

/*
 * Modelize an IDT Entry
 */
struct _kidt_entry {
	/*  */
	uint16_t base_lower;
	/*  */
	uint16_t ksel;
	/*  */
	uint8_t __padd_check;
	/*  */
	uint8_t flags;
	/*  */
	uint16_t base_high;
} __attribute__ ((packed));

typedef struct _kidt_entry interrupt_entry_t;

/*
 * IDT pointer container
 */
struct _kidt_ptr {
	uint16_t limit;
	uint32_t base;
} __attribute__ ((packed));

typedef struct _kidt_ptr idt_ptr_t;

/* PROTOTYPES */

void idt_add_entry(uint8_t index, uint32_t base,
			  uint16_t ksel, uint8_t flags);
void install_system_idt(void);

/* ASSEMBLY PROTOTYPES */

extern void _idt_commit(uint32_t);

#endif	/* IRQ_H */
