  ;; Multiboot spec implementation:
  ;;-------------------------------
  ;; See:
  ;;  - https://wiki.osdev.org/Multiboot
  ;;  - https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#Header-magic-fields
  ;;  - https://www.gnu.org/software/grub/manual/multiboot/html_node/boot_002eS.html#boot_002eS
  bits 32

  section .multiboot
        align 4
        dd 0x1BADB002           ; MAGIC
        ;; When 0 in the ‘flags’ word is set, then all boot modules loaded along
        ;; with the operating system must be aligned on page (4KB) boundaries.
        ;; Some operating systems expect to be able to map the pages containing boot
        ;; modules directly into a paged address space during startup, and thus need
        ;; the boot modules to be page-aligned.
        dd 0x00
        ;; The field ‘checksum’ is a 32-bit unsigned value which, when added to
        ;; the other magic fields (i.e. ‘magic’ and ‘flags’),
        ;; must have a 32-bit unsigned sum of zero.
        dd - (0x1BADB002 + 0x00)
