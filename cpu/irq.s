EXTERN irq_handler
irq_common:
	pushad
	mov ax, ds
	push eax
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	push esp ; c handler takes a pointer to regs
	call irq_handler
	add esp, 4

	pop eax 
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	popad
	add esp, 8
	iret

GLOBAL irq0
GLOBAL irq1
GLOBAL irq2
GLOBAL irq3
GLOBAL irq4
GLOBAL irq5
GLOBAL irq6
GLOBAL irq7
GLOBAL irq8
GLOBAL irq9
GLOBAL irq10
GLOBAL irq11
GLOBAL irq12
GLOBAL irq13
GLOBAL irq14
GLOBAL irq15

; some interrupts push an error code, here the error code is the irq number

irq0:
	push DWORD 0
	push DWORD 32
	jmp irq_common

irq1:
	push DWORD 1
	push DWORD 33
	jmp irq_common

irq2:
	push DWORD 2
	push DWORD 34
	jmp irq_common

irq3:
	push DWORD 3
	push DWORD 35
	jmp irq_common

irq4:
	push DWORD 4
	push DWORD 36
	jmp irq_common

irq5:
	push DWORD 5
	push DWORD 37
	jmp irq_common

irq6:
	push DWORD 6
	push DWORD 38
	jmp irq_common

irq7:
	push DWORD 7
	push DWORD 39
	jmp irq_common

irq8:
	push DWORD 8
	push DWORD 40
	jmp irq_common

irq9:
	push DWORD 9
	push DWORD 41
	jmp irq_common

irq10:
	push DWORD 10
	push DWORD 42
	jmp irq_common

irq11:
	push DWORD 11
	push DWORD 43
	jmp irq_common

irq12:
	push DWORD 12
	push DWORD 44
	jmp irq_common

irq13:
	push DWORD 13
	push DWORD 45
	jmp irq_common

irq14:
	push DWORD 14
	push DWORD 46
	jmp irq_common

irq15:
	push DWORD 15
	push DWORD 47
	jmp irq_common