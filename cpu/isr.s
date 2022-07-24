EXTERN isr_handler
isr_common:
	pushad
	mov ax, ds
	push eax
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	push esp ; c handler takes a pointer to the interrupt frame as argument
			 ; to be able to modify the registers directly
	call isr_handler
	add esp, 4

	pop eax 
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	popad
	add esp, 8
	sti
	iret

GLOBAL isr0
GLOBAL isr1
GLOBAL isr2
GLOBAL isr3
GLOBAL isr4
GLOBAL isr5
GLOBAL isr6
GLOBAL isr7
GLOBAL isr8
GLOBAL isr9
GLOBAL isr10
GLOBAL isr11
GLOBAL isr12
GLOBAL isr13
GLOBAL isr14
GLOBAL isr15
GLOBAL isr16
GLOBAL isr17
GLOBAL isr18
GLOBAL isr19
GLOBAL isr20
GLOBAL isr21
GLOBAL isr22
GLOBAL isr23
GLOBAL isr24
GLOBAL isr25
GLOBAL isr26
GLOBAL isr27
GLOBAL isr28
GLOBAL isr29
GLOBAL isr30
GLOBAL isr31

; some interrupts automatically push an error code, some don't
; those that don't, manually push a zero error code
; before the vector is pushed

isr0:
	cli
	push DWORD 0
	push DWORD 0
	jmp isr_common

isr1:
	cli
	push DWORD 0
	push DWORD 1
	jmp isr_common

isr2:
	cli
	push DWORD 0
	push DWORD 2
	jmp isr_common

isr3:
	cli
	push DWORD 0
	push DWORD 3
	jmp isr_common

isr4:
	cli
	push DWORD 0
	push DWORD 4
	jmp isr_common

isr5:
	cli
	push DWORD 0
	push DWORD 5
	jmp isr_common

isr6:
	cli
	push DWORD 0
	push DWORD 6
	jmp isr_common

isr7:
	cli
	push DWORD 0
	push DWORD 7
	jmp isr_common

isr8:
	cli
	push DWORD 8
	jmp isr_common

isr9:
	cli
	push DWORD 0
	push DWORD 9
	jmp isr_common

isr10:
	cli
	push DWORD 10
	jmp isr_common

isr11:
	cli
	push DWORD 11
	jmp isr_common

isr12:
	cli
	push DWORD 12
	jmp isr_common

isr13:
	cli
	push DWORD 13
	jmp isr_common

isr14:
	cli
	push DWORD 14
	jmp isr_common

isr15:
	cli
	push DWORD 0
	push DWORD 15
	jmp isr_common

isr16:
	cli
	push DWORD 0
	push DWORD 16
	jmp isr_common

isr17:
	cli
	push DWORD 17
	jmp isr_common

isr18:
	cli
	push DWORD 0
	push DWORD 18
	jmp isr_common

isr19:
	cli
	push DWORD 0
	push DWORD 19
	jmp isr_common

isr20:
	cli
	push DWORD 0
	push DWORD 20
	jmp isr_common

isr21:
	cli
	push DWORD 21
	jmp isr_common

isr22:
	cli
	push DWORD 0
	push DWORD 22
	jmp isr_common

isr23:
	cli
	push DWORD 0
	push DWORD 23
	jmp isr_common

isr24:
	cli
	push DWORD 0
	push DWORD 24
	jmp isr_common

isr25:
	cli
	push DWORD 0
	push DWORD 25
	jmp isr_common

isr26:
	cli
	push DWORD 0
	push DWORD 26
	jmp isr_common

isr27:
	cli
	push DWORD 0
	push DWORD 27
	jmp isr_common

isr28:
	cli
	push DWORD 0
	push DWORD 28
	jmp isr_common

isr29:
	cli
	push DWORD 29
	jmp isr_common

isr30:
	cli
	push DWORD 30
	jmp isr_common

isr31:
	cli
	push DWORD 0
	push DWORD 31
	jmp isr_common
