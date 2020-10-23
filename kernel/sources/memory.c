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

/* Reference from linker file */
extern uint32_t physmemstart;

/* Memory referenced from linker value */
kheap_t served_address = (uint32_t)&physmemstart;

void __attribute__ ((cold))
install_system_memory(void)
{
	return ;
}
