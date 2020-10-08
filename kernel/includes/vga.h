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

/*
 * See: https://en.wikipedia.org/wiki/VGA_text_mode
 */

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

#define VGA_DEFAULT_BG BLACK
#define VGA_DEFAULT_FG WHITE

/* Video Buffer */
extern uint16_t *vga_buffer;

/* INTERNAL FUNCTIONS */

void vga_clear_screen(void);
void vga_swrite(const char *buff, uint32_t nbytes,
		uint8_t fg, uint8_t bg);
void vga_putcchar(const char c, uint8_t fg, uint8_t bg);
void vga_putchar(const char c);
void vga_putnbr(int n);
void vga_delchar(void);
void vga_puts(const char *buff);
void vga_endl(void);
void vga_puthex(uint32_t addr);

#endif	/* VGA_H */
