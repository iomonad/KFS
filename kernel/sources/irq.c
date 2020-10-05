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
#include <types.h>
#include <kernel.h>

interrupt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

/*
 * Interrupt handler called
 * by our assembly stub.
 */
void interrupt_handler(registers_t reg)
{
	vga_puts("Kernel got interrupt!\n");
	vga_putchar((char)reg.int_number);
}

void idt_add_entry(uint8_t index, uint32_t base,
		   uint16_t ksel, uint8_t flags)
{
	/* Set Memory Bases */
	idt_entries[index].base_lower = base & 0xFFFF;
	idt_entries[index].base_high = (base >> 16) & 0xFFFF;

        /* Kernel Selector */
	idt_entries[index].ksel = ksel;

	/* This field should always be @ 0 */
	idt_entries[index].__padd_check = 0x0;

	/* Set flags */
	idt_entries[index].flags = flags;
}

void __attribute__ ((cold))
install_system_idt(void)
{
	idt_ptr.limit = sizeof(interrupt_entry_t) * 256 - 1;
	idt_ptr.base = (uint32_t)&idt_entries;

	idt_add_entry(0, (uint32_t)irq0 , 0x08, 0x8E);
	idt_add_entry(1, (uint32_t)irq1 , 0x08, 0x8E);
	idt_add_entry(2, (uint32_t)irq2 , 0x08, 0x8E);

	_idt_commit((uint32_t)&idt_ptr);
}
