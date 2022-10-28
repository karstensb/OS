#define false 0
#define true 1

.extern isr_handler
.macro isr vector, dummy_error_code /* do we need to push an error code? */
	.global isr\vector
	isr\vector:
		cli
	.if \dummy_error_code
		pushl $0
	.endif
		pushl $\vector
		pushal
		pushw %ds
		pushw %es
		pushw %fs
		pushw %gs

		movw $0x10, %ax
		movw %ds, %ax
		movw %es, %ax
		movw %fs, %ax
		movw %gs, %ax
		/* the c handler takes a pointer to the interrupt frame */
		pushl %esp
		call isr_handler
		add $4, %esp

		popw %gs
		popw %fs
		popw %es
		popw %ds
		popal
	.if \dummy_error_code
		add $8, %esp
	.else
		add $4, %esp
	.endif
		sti
		iret
.endm

isr vector=0, dummy_error_code=false
isr vector=1, dummy_error_code=false
isr vector=2, dummy_error_code=false
isr vector=3, dummy_error_code=false
isr vector=4, dummy_error_code=false
isr vector=5, dummy_error_code=false
isr vector=6, dummy_error_code=false
isr vector=7, dummy_error_code=false
isr vector=8, dummy_error_code=true
isr vector=9, dummy_error_code=false
isr vector=10, dummy_error_code=true
isr vector=11, dummy_error_code=true
isr vector=12, dummy_error_code=true
isr vector=13, dummy_error_code=true
isr vector=14, dummy_error_code=true
isr vector=15, dummy_error_code=false
isr vector=16, dummy_error_code=false
isr vector=17, dummy_error_code=true
isr vector=18, dummy_error_code=false
isr vector=19, dummy_error_code=false
isr vector=20, dummy_error_code=false
isr vector=21, dummy_error_code=true
isr vector=22, dummy_error_code=false
isr vector=23, dummy_error_code=false
isr vector=24, dummy_error_code=false
isr vector=25, dummy_error_code=false
isr vector=26, dummy_error_code=false
isr vector=27, dummy_error_code=false
isr vector=28, dummy_error_code=false
isr vector=29, dummy_error_code=true
isr vector=30, dummy_error_code=true
isr vector=31, dummy_error_code=false
