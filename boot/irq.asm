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
