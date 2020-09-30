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

/*
 * Qwerty Layout
 */
__k_equivalence __ascii_key_table[] = {
	{0x1E, 'A'},
	{0x30, 'B'},
	{0x2E, 'C'},
	{0x20, 'D'},
	{0x12, 'E'},
	{0x21, 'F'},
	{0x22, 'G'},
	{0x23, 'H'},
	{0x17, 'I'},
	{0x24, 'J'},
	{0x25, 'K'},
	{0x26, 'L'},
	{0x32, 'M'},
	{0x31, 'N'},
	{0x18, 'O'},
	{0x19, 'P'},
	{0x10, 'Q'},
	{0x13, 'R'},
	{0x1F, 'S'},
	{0x14, 'T'},
	{0x16, 'U'},
	{0x2F, 'V'},
	{0x11, 'W'},
	{0x2D, 'X'},
	{0x15, 'Y'},
	{0x2C, 'Z'},
	{0x02, '1'},
	{0x03, '2'},
	{0x04, '3'},
	{0x05, '4'},
	{0x06, '5'},
	{0x07, '6'},
	{0x08, '7'},
	{0x09, '8'},
	{0x0A, '9'},
	{0x0B, '0'},
};

/*
 * Writer implementation
 * https://pdos.csail.mit.edu/6.828/2011/readings/i386/IN.htm
 */
static inline uint8_t
input_kb(uint16_t kb_port)
{
	uint8_t read;

	asm volatile("inb %1, %0" : "=a"(read) : "d"(kb_port));
	return read;
}

/*
 * Reader implementation
 * https://pdos.csail.mit.edu/6.828/2011/readings/i386/OUT.htm
 */
static inline void
output_kb(uint16_t kb_port, uint8_t data)
{
	asm volatile("outb %0, %1" : "=a"(data) : "d"(kb_port));
}

/*
 * Get key input frow keyport
 * hardware port
 */
char kgetkey(void)
{
	char c = 0;

	while ((c = input_kb(KEYBOARD_PORT)) != 0) {
		if (likely(c >= 0)) {
			goto _valid;
		}
	}
_valid:
	return c;
}

/*
 * Convert input key to ascii
 * equivalent
 */
char keytoascii(const char key)
{
	uint32_t tsize;

	tsize = sizeof(__ascii_key_table) / sizeof(__ascii_key_table[0]);
	for (uint32_t i = 0; i < tsize; i++) {
		if (__ascii_key_table[i].k == key) {
			return __ascii_key_table[i].eq;
		}
	}
	return 0x00;
}


void input_vga_showcase(void) {

	char ch = 0;
	char keycode = 0;

	do {
		keycode = kgetkey();
		if(keycode == KEY_ENTER) {
			vga_endl();
		} else if (keycode == KEY_BACKSPACE) {
			vga_delchar();
		} else {
			ch = keytoascii(keycode);
			vga_putchar(ch);
		}
		ksleep(KERNEL_STD_DELAY);
	} while(ch >= 0);

}
