/* entry point of our kernel */
ENTRY(kfs_entry)

/* Setup kernel in hh memory */
kmem_pos = 0xC0000000;

SECTIONS
{
   . = 0x00100000;

   .multiboot : {
         *(.multiboot)
   }

   .boottext : {
         *(.boottext)
   }

   . += kmem_pos;

   kernel_memory_start = .;
   /* TEXT */
   .text ALIGN(4K) : AT(ADDR(.text) - kmem_pos) {
   	 section_text_start = .;
	 *(.text*)
   	 section_text_end = .;
   }

   /* RODATA */
   .rodata ALIGN(4K) : AT(ADDR(.rodata) - kmem_pos) {
     	 section_rodata_start = .;
	 *(.rodata*)
     	 section_rodata_end = .;
   }

   /* DATA */
   .data ALIGN(4K) : AT(ADDR(.data) - kmem_pos) {
     	 section_data_start = .;
         *(.data*)
     	 section_data_end = .;
   }

   /* BSS */
   .bss ALIGN(4K) : AT(ADDR(.bss) - kmem_pos) {
     	 section_bss_start = .;
   	*(COMMON)
      	*(.bss)
     	 section_bss_end = .;
   }

   /* Start of physical memory */
   physmemstart = .; _physmemstart = .; __physmemstart = .;
}
