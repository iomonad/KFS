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
#include <stdlib.h>
#include <kernel.h>

interrupt_entry_t idt_entries[IDT_SIZE];
irqcb_t interrupt_callbacks[IDT_SIZE];
idt_ptr_t idt_ptr;

/* Register Callback */
void register_interrupt_callback(uint8_t n, irqcb_t callback)
{
	interrupt_callbacks[n] = callback;
}

/*
 * Interrupt handler called
 * by our assembly stub.
 */
void interrupt_handler(registers_t reg)
{
	/*
	 * TODO:
	 *  - Handle EOI (end of interrupt) signal to the PICs.
	 *  - Send reset signal to master
	 */

	if (interrupt_callbacks[reg.int_number] != 0) {
		irqcb_t handler = interrupt_callbacks[reg.int_number];
		handler(reg);
	} else {
		vga_puts("Warning! No handler for interrupt: ");
		vga_putnbr(reg.int_number);
		vga_endl();
	}
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
	idt_ptr.limit = sizeof(interrupt_entry_t) * IDT_SIZE - 1;
	idt_ptr.base = (uint32_t)&idt_entries;

	memset((void*)&idt_entries, 0, sizeof(interrupt_entry_t) * IDT_SIZE);

	/* Populate Gates */
	idt_add_entry(0, (uint32_t)irq0, 0x08, 0x8E);
	idt_add_entry(1, (uint32_t)irq1, 0x08, 0x8E);
	idt_add_entry(2, (uint32_t)irq2, 0x08, 0x8E);
	idt_add_entry(3, (uint32_t)irq3, 0x08, 0x8E);
	idt_add_entry(4, (uint32_t)irq4, 0x08, 0x8E);
	idt_add_entry(5, (uint32_t)irq5, 0x08, 0x8E);
	idt_add_entry(6, (uint32_t)irq6, 0x08, 0x8E);
	idt_add_entry(7, (uint32_t)irq7, 0x08, 0x8E);
	idt_add_entry(8, (uint32_t)irq8, 0x08, 0x8E);
	idt_add_entry(9, (uint32_t)irq9, 0x08, 0x8E);
	idt_add_entry(10, (uint32_t)irq10, 0x08, 0x8E);
	idt_add_entry(11, (uint32_t)irq11, 0x08, 0x8E);
	idt_add_entry(12, (uint32_t)irq12, 0x08, 0x8E);
	idt_add_entry(13, (uint32_t)irq13, 0x08, 0x8E);
	idt_add_entry(14, (uint32_t)irq14, 0x08, 0x8E);
	idt_add_entry(15, (uint32_t)irq15, 0x08, 0x8E);
	idt_add_entry(16, (uint32_t)irq16, 0x08, 0x8E);
	idt_add_entry(17, (uint32_t)irq16, 0x08, 0x8E);
	idt_add_entry(18, (uint32_t)irq16, 0x08, 0x8E);
	idt_add_entry(19, (uint32_t)irq16, 0x08, 0x8E);
	idt_add_entry(20, (uint32_t)irq16, 0x08, 0x8E);
	idt_add_entry(21, (uint32_t)irq16, 0x08, 0x8E);
	idt_add_entry(22, (uint32_t)irq16, 0x08, 0x8E);
	idt_add_entry(23, (uint32_t)irq16, 0x08, 0x8E);
	idt_add_entry(24, (uint32_t)irq16, 0x08, 0x8E);
	idt_add_entry(25, (uint32_t)irq16, 0x08, 0x8E);
	idt_add_entry(26, (uint32_t)irq16, 0x08, 0x8E);
	idt_add_entry(27, (uint32_t)irq16, 0x08, 0x8E);
	idt_add_entry(28, (uint32_t)irq16, 0x08, 0x8E);
	idt_add_entry(29, (uint32_t)irq16, 0x08, 0x8E);
	idt_add_entry(30, (uint32_t)irq16, 0x08, 0x8E);
	idt_add_entry(31, (uint32_t)irq16, 0x08, 0x8E);

	_idt_commit((uint32_t)&idt_ptr);
}
