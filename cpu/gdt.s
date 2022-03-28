SECTION .data

KERNEL_CS equ gdt_kernel_cs - gdt_start
KERNEL_DS equ gdt_kernel_ds - gdt_start
USER_CS equ gdt_user_cs - gdt_start
USER_DS equ gdt_user_ds - gdt_start
GDT_TSS equ gdt_tss - gdt_start
TSS_SIZE equ tss_end - tss_start

gdt_start:
	dd 0x0
	dd 0x0

gdt_kernel_cs: 
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 0b10011010
	db 0b11001111
	db 0x0

gdt_kernel_ds:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 0b10010010
	db 0b11001111
	db 0x0

gdt_user_cs:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 0b11111010
	db 0b11001111
	db 0x0

gdt_user_ds:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 0b11110010
	db 0b11001111
	db 0x0

gdt_tss:
	dw TSS_SIZE & 0xFF
	dw (tss_start - $$) & 0xFF
	db ((tss_start - $$) >> 16) & 0xF
	db 0b10001001
	db 0b01000000 | ((TSS_SIZE >> 16) & 0x0F)
	db ((tss_start - $$) >> 24) & 0xF

gdt_end:

gdt_descriptor:
	dw gdt_end - gdt_start - 1
	dd gdt_start

tss_start:
	resb 128
tss_end: