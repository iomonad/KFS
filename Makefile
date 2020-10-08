#
# (c) 2020 iomonad <iomonad@riseup.net>
#

include rules/environment.mk
include rules/assembly.mk
include rules/compiler.mk
include rules/linker.mk

TARGET = kfs.rom
TARGET_SYM = kfs.sym
TARGET_ISO = kfs.iso

# ==== BEGIN RULES ====

prepare:
	mkdir -p $(BUILD_DIR)

bootloader: prepare $(ASM_TARGETS)
boot/%.o: boot/%.asm
	printf "ASM\t\t%s\n" $<
	$(ASM) $(ASM_FLAGS) $< -o $@

kernel: $(KERNEL_TARGETS)
kernel/sources/%.o: kernel/sources/%.c
	printf "CC\t\t%s\n" $<
	$(CC) $(CFLAGS) -c $< -o $@

rom: bootloader kernel
	printf "\nLD\t\t%s\n" $(TARGET)
	$(LINKER) $(LFLAGS) $(ASM_TARGETS) $(KERNEL_TARGETS) -o $(TARGET)
	cp $(TARGET) $(TARGET).cpy && objcopy --only-keep-debug $(TARGET).cpy $(TARGET_SYM) && rm $(TARGET).cpy

post:
	strip $(TARGET)

iso: rom post
	mkdir -p $(ISODIR_BOOT)
	cp $(TARGET) $(ISODIR)/boot/$(TARGET)
	cp boot/grub.cfg $(ISODIR_BOOT)/grub.cfg
	grub-mkrescue -o $(TARGET_ISO) --compress=gz --themes="" --install-modules="multiboot" $(ISODIR)

clean:
	rm -fr $(BUILD_DIR) isodir
	rm -fr $(KERNEL_TARGETS) $(ASM_TARGETS) $(TARGET_SYM)

fclean: clean
	rm -f $(TARGET) *.iso

re: fclean rom

# ==== END RULES =====

.PHONY: prepare bootloader kernel rom post clean fclean
.DEFAULT_GOAL := rom
MAKEFLAGS += --silent --no-builtin-rules
