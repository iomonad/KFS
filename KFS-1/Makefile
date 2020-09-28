#
#
#

ASM = as
ASM_FLAGS = --32 -o boot.
ASM_SRC = boot/boot.S
BOOTLOADER_TARGET = build/boot.o

prepare:
	mkdir -p build/

bootloader: prepare
	$(ASM) $(ASM_FLAGS)  $(ASM_SRC) -o $(BOOTLOADER_TARGET)

