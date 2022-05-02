SECTION .multiboot

MAGIC equ 0xE85250D6
ARCH_i386 equ 0x0
HEADER_LENGTH equ header_end - header_start
CHECKSUM equ -(MAGIC + ARCH_i386 + HEADER_LENGTH)

HEADER_END_TAG equ 0x0
HEADER_MBI_TAG equ 0x1
HEADER_FLAGS_TAG equ 0x4
HEADER_ALIGNMENT_TAG equ 0x6

END_TAG equ 0
BOOT_CMD_TAG equ 1
BOOT_DEV_TAG equ 5
MEM_MAP_TAG equ 6

EGA_TEXT_FLAG equ 1 << 1

ALIGN 8
header_start:
	dd MAGIC
	dd ARCH_i386
	dd HEADER_LENGTH
	dd CHECKSUM

ALIGN 8
mbi_tag:
	dw HEADER_MBI_TAG
	dw 0x0
	dd mbi_tag_end - mbi_tag
	dd BOOT_DEV_TAG
	dd MEM_MAP_TAG
mbi_tag_end:

ALIGN 8
flags_tag:
	dw HEADER_FLAGS_TAG
	dw 0x0
	dd flags_tag_end - flags_tag
	dd EGA_TEXT_FLAG
flags_tag_end:

ALIGN 8
alignment_tag:
	dw HEADER_ALIGNMENT_TAG
	dw 0x0
	dd alignment_tag_end - alignment_tag
alignment_tag_end:

ALIGN 8
end_tag:
	dw HEADER_END_TAG
	dw 0x0
	dd end_tag_end - end_tag
end_tag_end:

header_end:
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

EXTERN kmain
EXTERN gdt_descr
GLOBAL _start

_start:
	cli
	mov ebp, stack_top
	mov esp, ebp
	lgdt [gdt_descr]
	jmp KERNEL_CS:load_segs
load_segs:
	mov ax, KERNEL_DS
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

	push ebx
	call kmain
	pop ebx

	cli
	hlt
	jmp $-1