/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#include <vga.h>
#include <kernel.h>

/* Initialize video buffer */
uint16_t *vga_buffer = (uint16_t*)VGA_ADDRESS;

void __kmain()
{
	vga_clear_screen();
	vga_puts("Sarah je pense a toi !!!! <3");
	return ;
}
