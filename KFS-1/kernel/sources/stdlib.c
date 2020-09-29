/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#include <kernel.h>

uint32_t strlen(const char *buff) {
	uint32_t i;

	i = 0;
	while (buff[i] != '\0') {
		i++;
	}
	return i;
}
