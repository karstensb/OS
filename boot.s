ALIGNED equ 1<<0
MEMINFO equ 1<<1
FLAGS equ ALIGNED | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

SECTION .multiboot
ALIGN 4
dd MAGIC
dd FLAGS
dd CHECKSUM

SECTION .bss
ALIGN 16
stack_bottom:
resb 16384
stack_top:

EXTERN kernel_main
SECTION .text
GLOBAL _start
_start:
	cli
	mov esp, stack_top
	lgdt [gdt_descriptor]
	jmp KERNEL_CS:load_segs
load_segs:
	mov ax, KERNEL_DS
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
	;mov ax, GDT_TSS
	;ltr ax
	call kernel_main

	cli
	hlt
	jmp $-1

%include "cpu/gdt.s"