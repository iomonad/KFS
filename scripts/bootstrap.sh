#!/bin/sh

KERNEL_TARGET=kfs.rom
QEMU_PLATFORM=qemu-system-x86_64
QEMU_OPTS=-curses -m 128 -s

if [ ! -f "${KERNEL_TARGET}" ]; then
    make -C $(pwd) rom
fi

${QEMU_PLATFORM} -kernel ${KERNEL_TARGET} ${QEMU_OPTS} $@
