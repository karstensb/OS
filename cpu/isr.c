#include <stdnoreturn.h>
#include <stdbool.h>
#include "isr.h"
#include "idt.h"
#include "pic.h"
#include "x86.h"
#include "drivers/screen.h"
#include "util/string.h"

const char *err_msg[] ={
	"Divide-by-Zero-Error",
	"Debug",
	"Non-Maskable-Interrupt",
	"Breakpoint",
	"Overflow",
	"Bound-Range",
	"Invalid-Opcode",
	"Device-Not-Available",
	"Double-Fault",
	"Coprocessor-Segment-Overrun",
	"Invalid-TSS",
	"Segment-Not-Present",
	"Stack",
	"General-Protection",
	"Page-Fault",
	"Reserved",
	"87 Floating-Point Exception-Pending",
	"Alignment-Check",
	"Machine-Check",
	"SIMD Floating-Point",
	"Reserved",
	"Control-Protection Exception",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Hypervisor Injection Exception",
	"VMM Communication Exception",
	"Security Exception",
	"Reserved"
};

noreturn void isr_handler(registers *regs){
	clear_screen();
	kprint("An Error occured!\nError: ");
	kprint(err_msg[regs->int_no]);
	kprint("\nCode: 0x");
	kprinti(regs->int_no, 16);
	if(regs->int_no == 14){
		kprint("\nPage Fault Address: 0x");
		kprinti(rcr2(), 16);
	}

	cli();
halt:	
	hlt();
	goto halt;
}

static void (*irq_handlers[16]) (registers *regs);

void register_irq_handler(int irq, void (*handler)(registers *regs)){
	irq_handlers[irq] = handler;
}

void irq_handler(registers *regs){
	int irq = regs->err_code;
	/* check for spurious interrupts */
	if (irq == 7){
		if (~(pic_get_isr() & (1 << 7)))
			return;
	}else if (irq == 15){
		if (~(pic_get_isr() & (1 << 15))){
			pic_eoi(2);
			return;
		}
	}
	if (!irq_handlers[irq]){
		kprint("Received IRQ ");
		kprinti(irq, 10);
		pic_eoi(irq);
		return;
	}
	(irq_handlers[irq])(regs);
	pic_eoi(irq);
}