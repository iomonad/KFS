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

/* Assembly Ref */
extern void *stack_bottom;
extern void *stack_top;

/* PROTOTYPES */
void __attribute__ ((cold)) install_system_memory(void);

/* API */
void *kmalloc(size_t size);

#endif	/* MEMORY_H */
