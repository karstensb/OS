#include <stdnoreturn.h>
#include <stdbool.h>
#include "isr.h"
#include "idt.h"
#include "pic.h"
#include "x86.h"
#include "drivers/screen.h"
#include "util/string.h"
#include "util/panic.h"

const char *interrupts[] ={
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
	char err_msg[100];
	char buf[10];
	strcat(err_msg, "An Error occured!\nError: ");
	strcat(err_msg, interrupts[regs->int_no]);
	strcat(err_msg, "\nCode: 0x");
	strcat(err_msg, to_hex(regs->err_code, buf));
	if(regs->int_no == 14){
		strcat(err_msg, "\nPage Fault Address: 0x");
		strcat(err_msg, to_hex(rcr2(), buf));
	}
	panic(err_msg);
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
		kprintc('\n');
		kprint("Received IRQ ");
		kprinti(irq, 10);
		kprintc('\n');
		pic_eoi(irq);
		return;
	}
	(irq_handlers[irq])(regs);
	pic_eoi(irq);
}