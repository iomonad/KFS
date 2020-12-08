#!/bin/sh

KERNEL_TARGET=kfs.rom
QEMU_PLATFORM=qemu-system-x86_64
QEMU_OPTS=-curses -serial stdio -vga std -m 128 -S

if [ ! -f "${KERNEL_TARGET}" ]; then
    make -C $(pwd) rom
fi

${QEMU_PLATFORM} -kernel ${KERNEL_TARGET} ${QEMU_OPTS} $@ &
gdb -ex "target remote localhost:1234" -ex "symbol-file ${KERNEL_TARGET}"
