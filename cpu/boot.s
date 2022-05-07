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

;-------------------------------------------------------------------------------
SECTION .boot

KERNEL_CS equ 0x8
KERNEL_DS equ 0x10

EXTERN kmain
EXTERN gdt_descr
EXTERN page_dir
EXTERN page_tables
EXTERN _kernel_start ; defined in linker script
EXTERN _kernel_end	; defined in linker script

GLOBAL _start

_start:
	cli

pg_setup:
	; each page_dir entry points to the page table at the same offset
	; i.e. page_dir[0] points to page_tables[0]
	; and here pag_dir[896] points to page_tables[896]
	mov edi, page_tables - 0xE0000000 + 896 * 4096
	mov esi, 0

pg_fill:
	cmp esi, _kernel_end
	jg pg_enable

	mov edx, esi
	or edx, 0x3 ; present, writable
	mov [edi], edx

	add esi, 4096
	add edi, 4
	jmp pg_fill

pg_enable:
	mov [page_dir - 0xE0000000 + 0*4], DWORD (page_tables - 0xE0000000 + 896 * 4096) + 0x3 ; add 0x3 to present and writable
	mov [page_dir - 0xE0000000 + 1*4], DWORD (page_tables - 0xE0000000 + 897 * 4096) + 0x3 ; can't use or because that's
	mov [page_dir - 0xE0000000 + 896*4], DWORD (page_tables - 0xE0000000 + 896 * 4096) + 0x3 ; too complex for the linker
	mov [page_dir - 0xE0000000 + 897*4], DWORD (page_tables - 0xE0000000 + 897 * 4096) + 0x3

	mov ecx, page_dir - 0xE0000000
	mov cr3, ecx

	mov ecx, cr0
	or ecx, (1 << 31) | (1 << 16) ; enable paging and write-protect
f:	mov cr0, ecx

	lea ecx, [pg_finish]
	jmp ecx ; jump to higher half kernel

SECTION .text

pg_finish:
	mov [page_dir], DWORD 0 ; unmap identity paged lower area
	mov [page_dir + 4], DWORD 0

	mov eax, cr3 ; flush tlb
	mov cr3, eax

	lgdt [gdt_descr]
	jmp KERNEL_CS:load_segs
load_segs:
	mov ax, KERNEL_DS
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

	mov ebp, stack_top
	mov esp, ebp

	add ebx, 0xE0000000 ; mbi structure will be mapped to above 0xE0000000, too
	push ebx
	call kmain
	pop ebx

	cli
	hlt
	jmp $-1