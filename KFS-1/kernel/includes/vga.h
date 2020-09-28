/*
 * (c) iomonad - <iomonad@riseup.net>
 */
#ifndef VGA_H
#define VGA_H

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

#define VGA_ADDRESS 0xB8000

#endif	/* VGA_H */
