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
#include <keyboard.h>

/*  */
static inline uint8_t
input_kb(uint16_t kb_port)
{
	uint8_t read;

	asm volatile("inb %1, %0" : "=a"(read) : "d"(kb_port));
	return read;
}

/*  */
static inline void
output_kb(uint16_t kb_port, uint8_t data)
{
	asm volatile("outb %0, %1" : "=a"(data) : "d"(kb_port));
}
