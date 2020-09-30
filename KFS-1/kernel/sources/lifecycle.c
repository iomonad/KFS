/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#include <kernel.h>

/*
 * See: https://wiki.osdev.org/Shutdown
 */
void __attribute__ ((cold)) kshutdown(void)
{
	switch (__running_platform) {
		case QEMU:
			__asm__ __volatile__( "\n\
                            movw $0x2000, %%ax;\n\
                            movw $0x0604, %%dx;\n\
                            outw %%ax, %%dx;   \n" : : : "%eax", "%edx");
			break;
	        case VIRTUALBOX:
			__asm__ __volatile__( "\n\
                            movw $0x3400, %%ax;\n\
                            movw $0x4004, %%dx;\n\
                            outw %%ax, %%dx;   \n" : : : "%eax", "%edx");
		        break;
	        case BARE_X86:
			asm volatile("mov %ax, 0x1000");
			asm volatile("mov %ax, %ss");
			asm volatile("mov %sp, 0xf000");
			asm volatile("mov %ax, 0x5307");
			asm volatile("mov %bx, 0x0001");
			asm volatile("mov %cx, 0x0003");
			asm volatile("int $0x15");
			break;
	        default:
			asm volatile("ret");
			break;
	}
}
