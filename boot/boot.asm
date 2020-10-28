  ;;
  ;; (c) 2020 iomonad <clement@trosa.io>
  ;; This is part of the KFS Project
  ;; See: https://github.com/iomonad/KFS
  ;;

  bits 32

  %define KMEM_POS     0xC0000000
  %define KMEM_POS_PHY 0x00000000

  ;;-------------------
  ;; Lowmem endpoint
  ;;-------------------
  section .boottext
  global kfs_entry
  kfs_entry:
        ;; Populate Page directory
        mov ecx, 1024
        mov esp, page_directory
        sub esp, KMEM_POS       ; Remap
        populate_pdir:
                mov DWORD [esp], 0x0 ; Initialize at 0
                add esp, 0x4
        loop populate_pdir      ; Iterate n time ecx

        mov esp, page_directory
        sub esp, KMEM_POS

        ;; The kernel is identity mapped because enabling paging does
        ;; not change the next instruction, which continues to be physical.
        ;; The CPU would instead page fault if there was no identity mapping.
        mov DWORD [esp], KMEM_POS_PHY + 131
        mov DWORD [esp + 4 * (KMEM_POS >> 22)], KMEM_POS_PHY + 131

        ;; Enable paging
        mov ecx, page_directory
        sub ecx, KMEM_POS
        mov cr3, ecx            ; Push page table addr

        mov esp, cr4
        or esp, 0x00000010      ; Enable PSE (4M Pages)
        mov cr4, esp

        mov esp, cr0
        or esp, 0x80000001
        mov cr0, esp            ; Commit

        ;; Long jump into high mode
        lea ecx, [_kfs_entry_highmem]
        jmp ecx

  ;;------------------
  ;; Highmem endpoint
  ;;------------------
  section .text
  extern __kmain                ; Symbol defined in sources
  _kfs_entry_highmem:
        mov esp, _stack_top
        call __kmain
        hlt                     ; Enter halt state

  ;;-----
  ;; BSS
  ;;-----
  section .bss
  align 4096
  global page_directory         ; Page Directory Defined
  page_directory:
        resb 4096

  ;;-------------------------
  ;; Stack memory allocation
  ;;-------------------------
  section .bss
  global _stack_bottom
  global _stack_top

  align 4096
  _stack_bottom:
        resb 0x4000            ; Reserve 4kb Stack Memory
        align 4096
  _stack_top:
