#!/bin/sh

set -eux

TARGET=kfs.iso

if [ ! -f "$TARGET" ]; then
    echo "Warning: target $TARGET don't exists, building it"
    make iso
fi

bochs -f .bochsrc -q
