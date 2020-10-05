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

/*
 * Structure that modelize a
 * memory page.
 */
typedef struct page {
	uint32_t present :1;	/* Page is present in memory */
	uint32_t rw      :1;	/* Readonly if clear - RW if set */
	uint32_t user    :1;	/* HW level if clear */
	uint32_t access  :1;	/* Accessed since last page refresh ? */
	uint32_t dirty   :1;	/* Written since last refresh ? */
	uint32_t unused  :7;	/* Reserved bits */
	uint32_t frame   :20;	/* Frame Adress left shifted of 12bits */
} page_t;

#endif	/* MEMORY_H */
