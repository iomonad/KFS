/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#ifndef STDLIB_H
#define STDLIB_H

/* STRING */
uint32_t strlen(const char *buff);
uint32_t strcmp(const char *needle,
		const char *haystack);
uint32_t streq(const char *a, const char *b);

/* MEMORY */
void memset(void *dest, uint8_t val, uint32_t len);

#endif	/* STDLIB_H */
