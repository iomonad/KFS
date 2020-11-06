/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#include <vga.h>
#include <irq.h>
#include <time.h>
#include <memory.h>
#include <stdlib.h>
#include <kernel.h>
#include <lifecycle.h>

/*
 * Naive kmalloc implementation
 * TODO:
 *    - Implement priority
 */

void *kmalloc(size_t size)
{
	return stack_top + size;
}

void __attribute__ ((cold))
install_system_memory(void)
{
	return ;
}
