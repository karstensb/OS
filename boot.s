SECTION .multiboot

ALIGNED equ 1<<0
MEMINFO equ 1<<1
FLAGS equ ALIGNED | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

ALIGN 4
dd MAGIC
dd FLAGS
dd CHECKSUM

;-------------------------------------------------------------------------------
SECTION .bss

GLOBAL isr_stack_top

ALIGN 16
stack_bottom:
	resb 16384
stack_top:

isr_stack_bottom:
	resb 16384
isr_stack_top:

;------------------------------------------------------------------------------
SECTION .text

KERNEL_CS equ 0x8
KERNEL_DS equ 0x10

EXTERN kernel_main
EXTERN gdt_descriptor
GLOBAL _start

_start:
	cli
	mov ebp, stack_top
	mov esp, ebp
	lgdt [gdt_descriptor]
	jmp KERNEL_CS:load_segs
load_segs:
	mov ax, KERNEL_DS
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

	call kernel_main

	cli
	hlt
	jmp $-1