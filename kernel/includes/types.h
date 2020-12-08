/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#ifndef TYPES_H
#define TYPES_H

/* Concrete types */

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

/* Synthetic types
 * used for Unix function definition
 * compliance
 */

typedef unsigned short size_t;
typedef signed short ssize_t;

/* Naive OFF_T implementation */
typedef long int off_t;

#endif	/* TYPES_H */
