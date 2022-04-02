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

isr_stack_bottom:
	resb 16384
isr_stack_top:

EXTERN kernel_main
SECTION .text
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
fill_gdt_tss:
	mov eax, tss_start
	and eax, 0xFF
	or [gdt_tss + 2], eax
	mov eax, tss_start
	shr eax, 8
	and eax, 0xFF
	or [gdt_tss + 3], eax
	mov eax, tss_start
	shr eax, 16
	and eax, 0xFF
	or [gdt_tss + 4], eax
	mov eax, tss_start
	shr eax, 24
	and eax, 0xFF
	or [gdt_tss + 7], eax
init_tss:
	mov DWORD [tss_start + 4], isr_stack_top
	mov ax, GDT_TSS
	ltr ax

	call kernel_main

	cli
	hlt
	jmp $-1

%include "gdt.s"