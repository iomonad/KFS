  ;;
  ;; (c) 2020 iomonad <clement@trosa.io>
  ;; This is part of the KFS Project
  ;; See: https://github.com/iomonad/KFS
  ;;

  bits 32

  ;; Global Descriptor Table Implementation
  ;; See:
  ;; - https://wiki.osdev.org/Global_descriptor_table
  ;;
  ;; A vital part of the 386's various protection
  ;; measures is the GDT. It defines base accecss privilege
  ;; for certain parts of memory.
  ;; --
  ;; One of the key use is to generate violation exceptions
  ;; that give kernel a way to end process that
  ;; doing unauthorized memory access.
  ;; --
  ;; An important thing to know is that GRUB AUTOMATICALLY install
  ;; GDT when create rescue disk or installed on device.
  ;; If grub memory area is overrided, the GDT is trashed up
  ;; and will cause a 'Triple-Fault' (Basically will reset machine)
  ;; To prevent that, we should implement our own GDT in a place that
  ;; we know and have possibility to access.
  ;; --
  ;; * In short terms, to build our GDT, we should:
  ;;   - Tell processor were it is located
  ;;   - Load [CS-DS-ES-FS-GS] Registers to our entry.
  ;; * Behaviour to keep in mind:
  ;;   - The Code Segment (CS) tell processor which offset into
  ;;     the GDT that it will find the access privileges in which to
  ;;     execute the current code.
  ;;   - The Data Segment (DS) have the same idea but not for code,
  ;;     it's the Data segment and defines the access privileges for.
  ;;     the current data.
  ;;   - [ES,FS,GS] are used as alternate DS registers.
  ;; * GDT Architecture
  ;;   - It's a list of 64-bits long entries.
  ;;   - These entries define where in memory that the allowed region
  ;;     will start, as well as the limit of this region, and the
  ;;     access privileges associated with this entry.
  ;;   - It's important to have the first entry of our GDT set as NULL,
  ;;     also known as the `NULL Descriptor`.
  ;;   - Also, no segments regisers should be set to 0, otherwise it
  ;;     will raise a General Protection fault, an protection
  ;;     feature of the processor.
  global _gdt_commit
  extern _gdtptr                ; GDT Pointer globally defined

  _gdt_commit:
        lgdt [_gdtptr]          ; Load GDT to our global ptr
        mov ax, 0x10            ; Data segment offset from our GDT
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ss, ax
        jmp 0x08:_kflush        ; Code segment offset jump
  _kflush:
        ret                     ; Leave state and return to C implementation
