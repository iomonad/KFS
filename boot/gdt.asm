  ;;
  ;; (c) 2020 iomonad <clement@trosa.io>
  ;; This is part of the KFS Project
  ;; See: https://github.com/iomonad/KFS
  ;;

  bits 32

  ;; Global Descriptor Table Implementation
  ;; See:
  ;; - https://wiki.osdev.org/Global_descriptor_table
  ;; - https://wiki.osdev.org/GDT_Tutorial
  ;;
  section .text
  global __gdt_entrypoint

  __gdt_entrypoint:
        mov edx, [esp + 4]
        lgdt [edx]
        mov ax, 0x10            ; Selector
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ax, 0x18
        mov ss, ax
        jmp 0x08:_seg_reload
        _seg_reload:
        ret
