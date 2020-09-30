KERNEL_DIR = kernel/
KERNEL_SRC_DIR = $(addprefix $(KERNEL_DIR), sources/)
KERNEL_INC_DIR = $(addprefix $(KERNEL_DIR), includes/)

BUILD_DIR = build/
ISODIR = isodir
ISODIR_BOOT = $(ISODIR)/boot/grub
