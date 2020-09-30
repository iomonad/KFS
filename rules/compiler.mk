#
# (c) 2020 iomonad <iomonad@riseup.net>
#

CC = gcc
CFLAGS = -m32 -std=gnu99 \
	 -fno-builtin -fno-exceptions \
	 -fno-stack-protector \
	 -nostdlib -nodefaultlibs \
	 -Wshadow -Wunreachable-code -Wswitch-enum \
         -Wstrict-prototypes -Werror \
	 -O2 -Wall -Wextra -c $(LIBS_FLAGS)

LIBS_FLAGS = -I$(KERNEL_INC_DIR)
KERNEL_SRC_FILES = kernel.c vga.c keyboard.c stdlib.c time.c lifecycle.c
KERNEL_SOURCES = $(addprefix $(KERNEL_SRC_DIR), $(KERNEL_SRC_FILES))
KERNEL_TARGETS = $(KERNEL_SOURCES:.c=.o)
