  ;;
  ;; (c) 2020 iomonad <clement@trosa.io>
  ;; This is part of the KFS Project
  ;; See: https://github.com/iomonad/KFS
  ;;

  bits 32

  %define KMEM_POS     0xC0000000
  %define KMEM_POS_PHY 0x00000000

  ;; Lowmem endpoint
  section .boottext
  global kfs_entry
  kfs_entry:
        lea ecx, [_kfs_entry_highmem] ; Long jump into highmem mode
        jmp ecx

  ;; Highmem endpoint
  section .text
  extern __kmain                ; Symbol defined in sources
  _kfs_entry_highmem:
        cli
        mov esp, __stack_end
        call __kmain
        hlt                     ; Enter halt state

  ;; Stack memory allocation
  section .bss
  __stack:
        resb 0x4000            ; Reserve 4kb Stack Memory
  __stack_end:

  align 4096
  global page_directory
  page_directory:
        resb 4096
