/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#include <kernel.h>

/* STRING */

uint32_t strlen(const char *buff)
{
	uint32_t i;

	i = 0;
	while (buff[i] != '\0') {
		i++;
	}
	return i;
}

uint32_t strcmp(const char *needle,
		const char *haystack)
{
	while (*needle && (*needle == *haystack)) {
		needle++, haystack++;
	}
	return *(const uint32_t*)needle - *(const uint32_t*)haystack;
}

uint32_t streq(const char *a, const char *b)
{
	return strcmp(a, b) == 0;
}

/* MEMORY */

void memset(void *dest, uint8_t val, uint32_t len)
{
    uint8_t *x = (uint8_t *)dest;
    for ( ; len != 0; len--) *x++ = val;
}
