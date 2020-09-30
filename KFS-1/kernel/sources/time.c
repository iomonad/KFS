/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#include <kernel.h>

static inline void
__kernel_block_io(uint32_t wait_for)
{
	for (;;) {
		/* Prevent cpu wake up */
		asm volatile("nop");
		wait_for--;
		if (likely(wait_for <= 0)) {
			goto _done;
		}
	}
_done:
	return ;
}

/*
 * Kernel space sleep implementation
 */
void ksleep(uint32_t time)
{
	return __kernel_block_io(time);
}
