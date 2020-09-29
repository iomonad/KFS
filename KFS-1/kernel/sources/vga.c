/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#include <vga.h>
#include <stdlib.h>
#include <kernel.h>

extern uint16_t *vga_buffer;
extern uint16_t vga_buffer_cursor;
extern uint16_t vga_buffer_line_pos;
/*
 * Helper function to correctly
 * apply colorset on the desired
 * input character.
 */
static uint16_t vga_cook_char(unsigned char c,
			      uint8_t foreground,
			      uint8_t background)
{
	uint16_t ax;
	uint8_t ah, al;

	/*
	 *  16 bit video buffer elements(register ax)
	 *  -----------------------------------------
	 *   8 bits(ah) higher :
	 *      lower 4 bits - forec olor
	 *      higher 4 bits - back color
	 *
	 *   8 bits(al) lower :
	 *      8 bits : ASCII character to print
	 */
	ax = ah = al = 0x0;
	ah = background;
	ah <<= 4;
	ah |= foreground;
	ax = ah;
	ax <<= 8;
	al = c;
	ax |= al;
	return ax;
}

/*
 * Reset Screen state
 */
void vga_clear_screen(void)
{
	for (uint32_t i = 0; i < VGA_BUFFER_SIZE; ++i) {
		vga_buffer[i] = vga_cook_char(NULL, VGA_DEFAULT_FG, VGA_DEFAULT_BG);
	}
	vga_buffer_cursor = 0x0;
}

/*
 * Put char at position with color
 */
void vga_putcchar(const char c, uint8_t fg, uint8_t bg) {
	vga_buffer[vga_buffer_cursor] = vga_cook_char(c, fg, bg);
	vga_buffer_cursor++;
}

/*
 * Put char at position with default color
 */
void vga_putchar(const char c) {
	vga_putcchar(c, VGA_DEFAULT_FG, VGA_DEFAULT_BG);
}


/*
 * Secure VGA Write
 */
void vga_swrite(const char *buff, uint32_t nbytes,
		uint8_t fg, uint8_t bg)
{
	for (uint32_t i = 0; buff[i] != '\0' && i < nbytes; i++) {
		if (buff[i] == 0x0A) {
			vga_endl();
			continue ;
		} else if (buff[i] == 0x09) {
			vga_buffer_cursor += 0x08;
			continue ;
		}
		vga_buffer[vga_buffer_cursor] = vga_cook_char(buff[i], fg, bg);
		vga_buffer_cursor++;
	}
}

/*
 * Write call wrapper
 */
void vga_puts(const char *buff) {
	uint32_t len;

	len = strlen(buff);
	vga_swrite(buff, len, VGA_DEFAULT_FG, VGA_DEFAULT_BG);
}


/*
 * New line handler
 */
void vga_endl(void)
{
	/*
	 * Next Page Handling
	 */
	if (vga_buffer_line_pos >= 55) {
		vga_buffer_line_pos = 0x0;
		vga_clear_screen();
	}
	vga_buffer_cursor = 80 * vga_buffer_line_pos;
	vga_buffer_line_pos += 1;
}
