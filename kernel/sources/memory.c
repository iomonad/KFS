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

void *mmap(void *addr, size_t length, int prot,
	   int flags, int fd, off_t offset)
{
	(void)prot;
	(void)flags;
	(void)fd;
	(void)offset;

	(void)addr;
	(void)length;
	return NULL; 		/* TODO */
}

/*
 * Naive kmalloc implementation
 */

void *kmalloc(size_t size, int priority)
{
	(void)priority;
	return mmap(NULL, size, 0, 0, -1, 0);
}

void __attribute__ ((cold))
install_system_memory(void)
{
	return ;
}
