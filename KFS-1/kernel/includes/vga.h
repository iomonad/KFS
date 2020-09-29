/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#ifndef VGA_H
#define VGA_H

#include <types.h>

#define VGA_ADDRESS 0xB8000
#define VGA_BUFFER_SIZE 3200

enum vga_color {
	BLACK = 0x0,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	GREY,
	DARK_GREY,
	BRIGHT_BLUE,
	BRIGHT_GREEN,
	BRIGHT_CYAN,
	BRIGHT_RED,
	BRIGHT_MAGENTA,
	YELLOW,
	WHITE,
};

/* TODO DOCS */
uint16_t *vga_buffer;

#endif	/* VGA_H */
