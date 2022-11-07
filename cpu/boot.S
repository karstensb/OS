.section .multiboot

#define MAGIC 0xE85250D6
#define ARCH_i386 0x0
#define HEADER_LENGTH header_end - header_start
#define CHECKSUM -(MAGIC + ARCH_i386 + HEADER_LENGTH)

#define HEADER_END_TAG 0x0
#define HEADER_MBI_TAG 0x1
#define HEADER_FLAGS_TAG 0x4
#define HEADER_ALIGNMENT_TAG 0x6

#define END_TAG 0
#define BOOT_DEV_TAG 5
#define MEM_MAP_TAG 6

#define EGA_TEXT_FLAG 1 << 1

.align 8
header_start:
	.long MAGIC
	.long ARCH_i386
	.long HEADER_LENGTH
	.long CHECKSUM

.align 8
mbi_tag:
	.short HEADER_MBI_TAG
	.short 0x0
	.long mbi_tag_end - mbi_tag
	.long BOOT_DEV_TAG
	.long MEM_MAP_TAG
	.long 14
mbi_tag_end:

.align 8
flags_tag:
	.short HEADER_FLAGS_TAG
	.short 0x0
	.long flags_tag_end - flags_tag
	.long EGA_TEXT_FLAG
flags_tag_end:

.align 8
alignment_tag:
	.short HEADER_ALIGNMENT_TAG
	.short 0x0
	.long alignment_tag_end - alignment_tag
alignment_tag_end:

.align 8
end_tag:
	.short HEADER_END_TAG
	.short 0x0
	.long end_tag_end - end_tag
end_tag_end:

header_end:

/******************************************************************************/

.section .bss

.align 4096
.lcomm page_table_0, 4096

.align 16
.lcomm stack_top, 16384
stack:

/******************************************************************************/

.section .boot, "ax"

#define KERNEL_CS 0x8
#define KERNEL_DS 0x10

.extern kmain
.extern mbi
.extern gdt_descr
.extern page_dir
.extern _kernel_start /* defined in linker script */
.extern _kernel_end	/* defined in linker script */

.global _start

_start:
mbi_setup:
	movl %ebx, %esi
	movl $(_kernel_end), %edi
	movl (%ebx), %ecx
	rep
	movsb
	mov $(_kernel_end), %ebx

pg_setup:
	movl $(page_table_0 - 0xE0000000), %edi
	movl $0, %esi
	movl $(_kernel_end), %ecx
	add (%ebx), %ecx /* reserve space for teh mbi */

pg_fill:
	cmp %ecx, %esi
	jg pg_enable

	movl %esi, %edx
	or $0x1, %edx /* page is present */
	movl %edx, (%edi)

	add $4096, %esi
	add $4, %edi
	jmp pg_fill

pg_enable:
	movl $(page_table_0 - 0xE0000000 + 0x1), page_dir - 0xE0000000 + 0*4
	movl $(page_table_0 - 0xE0000000 + 0x1), page_dir - 0xE0000000 + 896*4
	movl $(page_dir - 0xE0000000 + 0x1), page_dir - 0xE0000000 + 1023*4

	movl $(page_dir - 0xE0000000), %ecx
	movl %ecx, %cr3

	movl %cr0, %eax
	or $(1 << 31), %eax /* enable paging */
	movl %eax, %cr0

	lea pg_finish, %eax
	jmp *%eax /* jump to higher half kernel */

/******************************************************************************/

.section .text

pg_finish:
	movl $0, page_dir(,1) /* unmap identity mapped lower area */

	movl %cr3, %eax /* flush tlb */
	movl %eax, %cr3

	lgdt (gdt_descr)
	ljmp $(KERNEL_CS), $(load_segs)
load_segs:
	movw $(KERNEL_DS), %ax
	movw %ax, %ds
	movw %ax, %ss
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs

	movl $(stack - 16384), %ebp
	movl %ebp, %esp

	finit

	add $0xE0000000, %ebx /* mbi structure is mapped to above 0xE0000000, too */
	movl %ebx, mbi /* mov mbi loation to the mbi variable from c code */
	call kmain

	cli
	hlt
	jmp .-1