TARGET = kfs.rom

ASM = as
ASM_FLAGS = --32 -o boot.
ASM_SRC = boot/boot.S
BOOTLOADER_TARGET = build/boot.o

CC = gcc
CFLAGS = -m32 -std=gnu99 \
	 -fno-builtin -fno-exceptions \
	 -fno-stack-protector \
	 -nostdlib -nodefaultlibs \
	 -O2 -Wall -Wextra -c $(LIBS_FLAGS)
LIBS_FLAGS = -Ikernel/includes
KERNEL_SOURCES = kernel/sources/kernel.c
KERNEL_TARGET = build/kernel.o

LINKER = ld
LFLAGS = -m elf_i386 -T linker.ld -nostdlib

BUILD_DIR = build/

prepare:
	mkdir -p $(BUILD_DIR)

bootloader: prepare
	$(ASM) $(ASM_FLAGS)  $(ASM_SRC) -o $(BOOTLOADER_TARGET)

kernel: prepare
	$(CC) $(CFLAGS) $(KERNEL_SOURCES) -o $(KERNEL_TARGET)

rom: bootloader kernel
	$(LINKER) $(LFLAGS) $(BOOTLOADER_TARGET) $(KERNEL_TARGET) -o $(TARGET)

iso: rom
	mkdir -p isodir/boot/grub
	cp $(TARGET) isodir/boot/$(TARGET)
	cp boot/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o kfs.iso isodir

clean:
	rm -fr $(BUILD_DIR) isodir

.PHONY: prepare bootloader kernel rom
.DEFAULT_GOAL := rom
