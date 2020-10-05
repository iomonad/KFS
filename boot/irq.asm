  ;;
  ;; (c) 2020 iomonad <clement@trosa.io>
  ;; This is part of the KFS Project
  ;; See: https://github.com/iomonad/KFS
  ;;

  bits 32

  ;; Global Interrupt Table
  ;; assembly routine
  global _idt_commit

  _idt_commit:
        mov eax, [esp+4]        ; Load memory pointer
        lidt [eax]              ; Store IDT pointer on
        ret

  ;;
  ;; Interrups implementations
  ;;
  extern interrupt_handler      ; High level Handler

  ;; IRQ Stub:
  ;;  - Save processor state
  ;;  - Setup kernel mode segment
  ;;  - Call Highlevel C Handler
  ;;  - Restore the stackframe
  ;;
  interrupt_stub:
        pusha                   ; Push all general purpose registers

        mov ax, ds              ; low 16bits eax
        push eax                ; save data segment descriptor

        mov ax, 0x10            ; load the kernel data segment descriptor
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax

        call interrupt_handler  ; C Implementations

        pop eax                 ; Reload data segment descriptor
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax

        popa                    ; Pop all gener purpose registers
        add esp, 8              ; Clean parameters
        sti

        ;;
        ;; See: https://www.felixcloutier.com/x86/iret:iretd
        ;;
        ;; See the section titled “Task Linking” in Chapter 7 of
        ;; the Intel® 64 and IA-32 Architectures Software
        ;; Developer’s Manual, Volume 3A.
        ;;
        iret                    ; Interrupt Return

  ;;
  ;; Routine Implementation
  ;;
  %macro IRQ_NO_ERR 1
        global irq%1
        irq%1:
          cli                   ; Clean Interrupt Flag
          push byte 0
          push byte %1          ; Push ID
          jmp interrupt_stub
  %endmacro

  %macro IRQ_ERR 1
        global irq%1
        irq%1:
          cli                   ; Clean Interrupt Flag
          push byte %1          ; Push ID
          jmp interrupt_stub
  %endmacro

  ;; Create Interrupt here
  IRQ_NO_ERR 0
  IRQ_NO_ERR 1
  IRQ_NO_ERR 2
