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

void __kmain()
{
	/* Initialize video buffer */
	vga_buffer = (uint16_t*)VGA_ADDRESS;

	return ;
}
