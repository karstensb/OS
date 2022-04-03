EXTERN isr_handler
EXTERN tss_start
isr_common:
	pushad
	mov ax, ds
	push eax
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov eax, [tss_start + 4]
	add eax, 2048
	mov [tss_start + 4], eax
	sti

	call isr_handler

	cli
	mov eax, [tss_start + 4]
	sub eax, 2048
	mov [tss_start + 4], eax

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

isr0:
	cli
	push 0
	push 0
	jmp isr_common

isr1:
	cli
	push 0
	push 1
	jmp isr_common

isr2:
	cli
	push 0
	push 2
	jmp isr_common

isr3:
	cli
	push 0
	push 3
	jmp isr_common

isr4:
	cli
	push 0
	push 4
	jmp isr_common

isr5:
	cli
	push 0
	push 5
	jmp isr_common

isr6:
	cli
	push 0
	push 6
	jmp isr_common

isr7:
	cli
	push 0
	push 7
	jmp isr_common

isr8:
	cli
	push 8
	jmp isr_common

isr9:
	cli
	push 0
	push 9
	jmp isr_common

isr10:
	cli
	push 10
	jmp isr_common

isr11:
	cli
	push 11
	jmp isr_common

isr12:
	cli
	push 12
	jmp isr_common

isr13:
	cli
	push 13
	jmp isr_common

isr14:
	cli
	push 14
	jmp isr_common

isr15:
	cli
	push 0
	push 15
	jmp isr_common

isr16:
	cli
	push 0
	push 16
	jmp isr_common

isr17:
	cli
	push 17
	jmp isr_common

isr18:
	cli
	push 0
	push 18
	jmp isr_common

isr19:
	cli
	push 0
	push 19
	jmp isr_common

isr20:
	cli
	push 0
	push 20
	jmp isr_common

isr21:
	cli
	push 21
	jmp isr_common

isr22:
	cli
	push 0
	push 22
	jmp isr_common

isr23:
	cli
	push 0
	push 23
	jmp isr_common

isr24:
	cli
	push 0
	push 24
	jmp isr_common

isr25:
	cli
	push 0
	push 25
	jmp isr_common

isr26:
	cli
	push 0
	push 26
	jmp isr_common

isr27:
	cli
	push 0
	push 27
	jmp isr_common

isr28:
	cli
	push 0
	push 28
	jmp isr_common

isr29:
	cli
	push 29
	jmp isr_common

isr30:
	cli
	push 30
	jmp isr_common

isr31:
	cli
	push 0
	push 31
	jmp isr_common