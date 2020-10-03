# KFS ![Kernel Build CI](https://github.com/iomonad/KFS/workflows/Kernel%20Build%20CI/badge.svg?branch=master)
Kernel From Scratch: From basic bootable kernel to advanced ELF memory parser &amp; complete userspace implementation.

> Listing of project quest coverage

## KFS-1
- A kernel you can boot viaGRUB
- An ASM bootable base
- A basic kernel library, with basics functions and types
- Some basic code to print some stuff on the screen
- A basic "Hello world" kernel

## KFS-2
- GDT (Global Descriptor Table) Implementation
 -> Creation / Fill / Linkage

## KFS-3
- A complete memory code structure, with pagination handling
- Read and Write rights on memory
- User space memory and Kernel space memory
- Physical and Virtual memory
- Code helpers for physical memory, likekmalloc,kfree,ksize,kbrk
- Code helpers for virtual memory, likevmalloc,vfree,vsize,vbrk
- Kernel Panic handling
