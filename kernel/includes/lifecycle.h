/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#ifndef LIFECYCLE_H
#define LIFECYCLE_H

void __attribute__ ((cold)) kshutdown(void);
void __attribute__ ((cold)) kpanic(const char *msg);

#endif	/* LIFECYCLE_H */
