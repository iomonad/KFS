/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#ifndef TIME_H
#define TIME_H

#include <types.h>

#define KERNEL_STD_DELAY 0x02FFFFFF

void ksleep(uint32_t time);

#endif	/* TIME_H */
