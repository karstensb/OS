ALIGNED equ 1<<0
MEMINFO equ 1<<1
FLAGS equ ALIGNED | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

SECTION .multiboot
align 4
dd MAGIC
dd FLAGS
dd CHECKSUM

SECTION .bss
align 16
stack_bottom:
resb 16384
stack_top:

extern kernel_main
SECTION .text
GLOBAL _start
_start:
	mov esp, stack_top
	lgdt [gdt_descriptor]
	jmp CODE_SEG:load_segs
load_segs:
	mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
	call kernel_main

	cli
	hlt
	jmp $-1
	
%include "boot/gdt.asm"