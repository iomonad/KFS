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
