#
# (c) 2020 iomonad <iomonad@riseup.net>
#

include rules/environment.mk
include rules/assembly.mk
include rules/compiler.mk
include rules/linker.mk

TARGET = kfs.rom
TARGET_ISO = kfs.iso

# ==== BEGIN RULES ====

prepare:
	mkdir -p $(BUILD_DIR)

bootloader: prepare
	$(ASM) $(ASM_FLAGS)  $(ASM_SRC) -o $(BOOTLOADER_TARGET)

kernel: $(KERNEL_TARGETS)

$(KERNEL_SRC_DIR)/%.o: $(KERNEL_SOURCES)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

rom: bootloader kernel
	$(LINKER) $(LFLAGS) $(BOOTLOADER_TARGET) $(KERNEL_TARGETS) -o $(TARGET)

post:
	strip $(TARGET)

iso: rom post
	mkdir -p $(ISODIR_BOOT)
	cp $(TARGET) $(ISODIR)/boot/$(TARGET)
	cp boot/grub.cfg $(ISODIR_BOOT)/grub.cfg
	grub-mkrescue -o $(TARGET_ISO) --compress=gz $(ISODIR)

clean:
	rm -fr $(BUILD_DIR) isodir
	rm -f $(KERNEL_TARGETS)

fclean: clean
	rm -f $(TARGET) *.iso

# ==== END RULES =====

.PHONY: prepare bootloader kernel rom post
.DEFAULT_GOAL := rom
