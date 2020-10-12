#!/bin/sh

set -eux

TARGET=kfs.rom

if [ ! -f "$TARGET" ]; then
    echo "Target $TARGET don't exists."
    exit 1
fi

if [ -f "/dev/loop0" ]; then
    echo "Warning: no loop devices available (maybe use 'modprobe loop' ?)"
    exit 1
fi

sudo /sbin/losetup -d /dev/loop0 || echo "Already unmounted"
sudo /sbin/losetup /dev/loop0 $TARGET
sudo bochs -f .bochsrc
sudo /sbin/losetup -d /dev/loop0
