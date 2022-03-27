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
	call isr_handler
	pop eax 
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	popad
	add esp, 8
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

isr0:
	push 0
	push 0
	jmp isr_common

isr1:
	push 0
	push 1
	jmp isr_common

isr2:
	push 0
	push 2
	jmp isr_common

isr3:
	push 0
	push 3
	jmp isr_common

isr4:
	push 0
	push 4
	jmp isr_common

isr5:
	push 0
	push 5
	jmp isr_common

isr6:
	push 0
	push 6
	jmp isr_common

isr7:
	push 0
	push 7
	jmp isr_common

isr8:
	push 8
	jmp isr_common

isr9:
	push 0
	push 9
	jmp isr_common

isr10:
	push 10
	jmp isr_common

isr11:
	push 11
	jmp isr_common

isr12:
	push 12
	jmp isr_common

isr13:
	push 13
	jmp isr_common

isr14:
	push 14
	jmp isr_common

isr15:
	push 0
	push 15
	jmp isr_common

isr16:
	push 0
	push 16
	jmp isr_common

isr17:
	push 17
	jmp isr_common

isr18:
	push 0
	push 18
	jmp isr_common

isr19:
	push 0
	push 19
	jmp isr_common

isr20:
	push 0
	push 20
	jmp isr_common

isr21:
	push 21
	jmp isr_common

isr22:
	push 0
	push 22
	jmp isr_common

isr23:
	push 0
	push 23
	jmp isr_common

isr24:
	push 0
	push 24
	jmp isr_common

isr25:
	push 0
	push 25
	jmp isr_common

isr26:
	push 0
	push 26
	jmp isr_common

isr27:
	push 0
	push 27
	jmp isr_common

isr28:
	push 0
	push 28
	jmp isr_common

isr29:
	push 29
	jmp isr_common

isr30:
	push 30
	jmp isr_common

isr31:
	push 0
	push 31
	jmp isr_common