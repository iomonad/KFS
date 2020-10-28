/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include <types.h>

extern void *kernel_memory_start;
#define KMEM_POS_START ((uint32_t*)&kernel_memory_start)

extern void *section_text_start;
extern void *section_text_end;
#define SECTION_TEXT_START ((uint32_t*)&section_text_start)
#define SECTION_TEXT_END ((uint32_t*)&section_text_end)

extern void *section_rodata_start;
extern void *section_rodata_end;
#define SECTION_RODATA_START ((uint32_t*)&section_rodata_start)
#define SECTION_RODATA_END ((uint32_t*)&section_rodata_end)

extern void *section_data_start;
extern void *section_data_end;
#define SECTION_DATA_START ((uint32_t*)&section_data_start)
#define SECTION_DATA_END ((uint32_t*)&section_data_end)

extern void *section_bss_start;
extern void *section_bss_end;
#define SECTION_BSS_START ((uint32_t*)&section_bss_start)
#define SECTION_BSS_END ((uint32_t*)&section_bss_end)

extern void *kernel_memory_end;
#define KMEM_POS_END ((uint32_t*)&kernel_memory_end)

#define KERNEL_MEMORY_SIZE (uint32_t)(KMEM_POS_END - KMEM_POS_START)

#endif
