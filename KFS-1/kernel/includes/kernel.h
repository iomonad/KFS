/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#ifndef KERNEL_H
#define KERNEL_H

#include <types.h>

/* SYSTEM CONSTANTS */

#define PAGE_SIZE 4096

#define NULL 0

/* OPTMISATIONS */
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

/* ENTRYPOINT */

void __kmain(void);

#endif	/* KERNEL_H */
