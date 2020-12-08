/*
 *
 * (c) 2020 iomonad <clement@trosa.io>
 *
 * This is part of the KFS Project
 * See: https://github.com/iomonad/KFS
 *
 */
#ifndef IRQ_H
#define IRQ_H

#include <types.h>

# define IDT_SIZE 256

/*
 * Modelize an IDT Entry
 */
struct _kidt_entry {
	uint16_t base_lower;
	uint16_t ksel;
	uint8_t __padd_check;
	uint8_t flags;
	uint16_t base_high;
} __attribute__ ((packed));
typedef struct _kidt_entry interrupt_entry_t;

/*
 * IDT pointer container
 */
struct _kidt_ptr {
	uint16_t limit;
	uint32_t base;
} __attribute__ ((packed));
typedef struct _kidt_ptr idt_ptr_t;

/*
 * Modelize input register
 */
typedef struct registers {
	uint32_t ds;					 /* DATASEGMENT */
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; /* PUSHA */
	uint32_t int_number, err_code;			 /* Interrupt code / err */
	uint32_t eip, cs, eflags, useresp, ss;		 /* Implicit push by processor */
} registers_t;

/*
 * See: https://wiki.osdev.org/Exceptions
 */

extern void irq0(void);		/* DIVIDE BY 0 */
extern void irq1(void);		/* DEBUG */
extern void irq2(void);		/* Non Maskable Interrupt */
extern void irq3(void);		/* Breakpoint */
extern void irq4(void);		/* Overflow */
extern void irq5(void);		/* Bound Range Exceeded */
extern void irq6(void);		/* Invalid Opcode */
extern void irq7(void);		/* Device Not Available */
extern void irq8(void);		/* Double Fault */
extern void irq9(void);		/* Coprocessor Segment Overrun */
extern void irq10(void);	/* Invalid TSS */
extern void irq11(void);	/* Segment Not Present */
extern void irq12(void);	/* Stack-Segment Fault */
extern void irq13(void);	/* General Protection Fault */
extern void irq14(void);	/* Page Fault */
extern void irq15(void);	/* Reserved */
extern void irq16(void);	/* x87 Floating-Point Exception */
extern void irq17(void);	/* Alignment Check */
extern void irq18(void);	/* Machine Check */
extern void irq19(void);	/* SIMD Floating-Point Exception */
extern void irq20(void);	/* Virtualization Exception */
extern void irq21(void);	/* Reserved */
extern void irq22(void);	/* Reserved */
extern void irq23(void);	/* Reserved */
extern void irq24(void);	/* Reserved */
extern void irq25(void);	/* Reserved */
extern void irq26(void);	/* Reserved */
extern void irq27(void);	/* Reserved */
extern void irq28(void);	/* Reserved */
extern void irq29(void);	/* Reserved */
extern void irq30(void);	/* Security Exception */
extern void irq31(void);	/* Reserved */

extern void _idt_commit(uint32_t); /* Commit */

/* Callback Register System */

typedef void (*irqcb_t)(registers_t);
void register_interrupt_callback(uint8_t n, irqcb_t callback);

/* Prototypes */

void idt_add_entry(uint8_t index, uint32_t base,
			  uint16_t ksel, uint8_t flags);
void install_system_idt(void);
void interrupt_handler(registers_t reg);


#endif	/* IRQ_H */
