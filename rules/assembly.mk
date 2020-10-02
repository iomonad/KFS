ASM = nasm
ASM_FLAGS = -f elf32
ASM_SRC_FILE = boot/boot.asm boot/gdt.asm
ASM_SRC = $(addprefix $(ASM_SRC_DIR), $(ASM_SRC_FILE))
ASM_TARGETS = $(ASM_SRC:.asm=.o)
