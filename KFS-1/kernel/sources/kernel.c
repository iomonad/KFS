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

/* Initialize video buffer */
uint16_t *vga_buffer = (uint16_t*)VGA_ADDRESS;
uint16_t vga_buffer_cursor = 0x00;
uint16_t vga_buffer_line_pos = 0x01;

void __kmain()
{
	vga_clear_screen();
	vga_puts("42");
	vga_endl();
	input_vga_showcase();
	return ;
}
