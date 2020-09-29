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

extern uint16_t *vga_buffer;

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
}

/*
 * Puts string on VGA
 */

void vga_puts(const char *str)
{
	for (int i = 0; str[i] != '\0'; i++) {
		vga_buffer[i] = vga_cook_char(str[i], VGA_DEFAULT_FG, VGA_DEFAULT_BG);
	}
}
