/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#include <irq.h>
#include <gdt.h>
#include <vga.h>
#include <time.h>
#include <memory.h>
#include <kernel.h>
#include <keyboard.h>
#include <lifecycle.h>

/* Initialize video buffer */
uint16_t *vga_buffer = (uint16_t*)VGA_ADDRESS;
uint16_t vga_buffer_cursor = 0x00;
uint16_t vga_buffer_line_pos = 0x01;

/* Initialize platform */
/* Need to auto determine in future */
__supported_platform __running_platform = QEMU;

static void __attribute__ ((cold))
__kernel_init_hook(void)
{
	/* Setup VGA */
	vga_clear_screen();

	/* Install GDT */
	install_system_gdt();
	vga_puts("GDT Installed!\n");

	/* Install IDT */
	install_system_idt();
	vga_puts("IDT Installed!\n");

	/* Initialize memory pagging */
	install_system_memory();
	vga_puts("Memory Paging Installed!\n");
}

void __kmain()
{
	/* Prepare kernel datastructures */
	__kernel_init_hook();

	for (;;) {
		asm volatile ("nop");
	}
        return kshutdown();
}
