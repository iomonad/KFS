/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#include <vga.h>
#include <time.h>
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

void __kmain()
{
	vga_clear_screen();
	vga_puts("42");
	vga_endl();
	vga_puts("System is going to halt !");
	ksleep(4000000000);
	return kshutdown();
}
