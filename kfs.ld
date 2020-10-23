/* entry point of our kernel */
ENTRY(kfs_entry)

/* Setup kernel in hh memory */
kmem_pos = 0xC0000000;

SECTIONS
{
   . = 0x100000;

   .multiboot ALIGN(4K) : {
         *(.multiboot*)
   }

   .boottext ALIGN(4K) : {
         *(.boottext*)
   }

   . += kmem_pos;
   kmem_start = .;

   /* TEXT */
   .text ALIGN(4K) : AT(ADDR(.text) - kmem_pos) {
   	 kmem_text_start = .;
	 *(.text*)
	 . = ALIGN(4K);
	 kmem_text_end = .;
   }

   /* RODATA */
   .rodata ALIGN(4K) : AT(ADDR(.rodata) - kmem_pos) {
  	  kmem_rodata_start = .;
	  *(.rodata*)
	  . = ALIGN(4K);
	  kmem_rodata_end = .;
   }

   /* DATA */
   .data ALIGN(4K) : AT(ADDR(.data) - kmem_pos) {
   	 kmem_data_start = .;
         *(.data*)
	 . = ALIGN(4K);
	kmem_data_end = .;
   }

   /* BSS */
   .bss ALIGN(4K) : AT(ADDR(.bss) - kmem_pos) {
   	kmem_bss_start = .;
      	*(.bss)
      	. = ALIGN(4K);
      	kmem_bss_end = .;
   }

   /* Start of physical memory */
   physmemstart = .; _physmemstart = .; __physmemstart = .;
}
