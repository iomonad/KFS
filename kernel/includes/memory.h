/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#ifndef MEMORY_H
#define MEMORY_H

#include <types.h>

typedef uint32_t kheap_t;

/* PROTOTYPES */

void __attribute__ ((cold)) install_system_memory(void);

/* API */
void *mmap(void *addr, size_t length, int prot,
	   int flags, int fd, off_t offset);

#endif	/* MEMORY_H */
