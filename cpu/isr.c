#include <stdnoreturn.h>
#include <stdbool.h>
#include "isr.h"
#include "idt.h"
#include "pic.h"
#include "util.h"
#include "../drivers/screen.h"
#include "../libc/string.h"

extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);

extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);

void isr_install(){
	cli();
	set_idt_trap(0, (uint32_t) isr0);
	set_idt_trap(1, (uint32_t) isr1);
	set_idt_trap(2, (uint32_t) isr2);
	set_idt_trap(3, (uint32_t) isr3);
	set_idt_trap(4, (uint32_t) isr4);
	set_idt_trap(5, (uint32_t) isr5);
	set_idt_trap(6, (uint32_t) isr6);
	set_idt_trap(7, (uint32_t) isr7);
	set_idt_trap(8, (uint32_t) isr8);
	set_idt_trap(9, (uint32_t) isr9);
	set_idt_trap(10, (uint32_t) isr10);
	set_idt_trap(11, (uint32_t) isr11);
	set_idt_trap(12, (uint32_t) isr12);
	set_idt_trap(13, (uint32_t) isr13);
	set_idt_trap(14, (uint32_t) isr14);
	set_idt_trap(15, (uint32_t) isr15);
	set_idt_trap(16, (uint32_t) isr16);
	set_idt_trap(17, (uint32_t) isr17);
	set_idt_trap(18, (uint32_t) isr18);
	set_idt_trap(19, (uint32_t) isr19);
	set_idt_trap(20, (uint32_t) isr20);
	set_idt_trap(21, (uint32_t) isr21);
	set_idt_trap(22, (uint32_t) isr22);
	set_idt_trap(23, (uint32_t) isr23);
	set_idt_trap(24, (uint32_t) isr24);
	set_idt_trap(25, (uint32_t) isr25);
	set_idt_trap(26, (uint32_t) isr26);
	set_idt_trap(27, (uint32_t) isr27);
	set_idt_trap(28, (uint32_t) isr28);
	set_idt_trap(29, (uint32_t) isr29);
	set_idt_trap(30, (uint32_t) isr30);
	set_idt_trap(31, (uint32_t) isr31);

	set_idt_gate(32, (uint32_t) irq0);
	set_idt_gate(33, (uint32_t) irq1);
	set_idt_gate(34, (uint32_t) irq2);
	set_idt_gate(35, (uint32_t) irq3);
	set_idt_gate(36, (uint32_t) irq4);
	set_idt_gate(37, (uint32_t) irq5);
	set_idt_gate(38, (uint32_t) irq6);
	set_idt_gate(39, (uint32_t) irq7);
	set_idt_gate(40, (uint32_t) irq8);
	set_idt_gate(41, (uint32_t) irq9);
	set_idt_gate(42, (uint32_t) irq10);
	set_idt_gate(43, (uint32_t) irq11);
	set_idt_gate(44, (uint32_t) irq12);
	set_idt_gate(45, (uint32_t) irq13);
	set_idt_gate(46, (uint32_t) irq14);
	set_idt_gate(47, (uint32_t) irq15);

	load_idt();
}

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

noreturn void isr_handler(registers_t regs){
	clear_screen();
	kprint("An Error occured!\nError: ");
	kprint(err_msg[regs.int_no]);
	kprint("\nCode: 0x");
	char err_code[5];
	kprint(itoa(regs.err_code, err_code, 16));

	cli();
halt:	
	hlt();
	goto halt;
}

static void (*irq_handlers[16]) (registers_t regs);

void register_irq(int irq, void (*handler)(registers_t regs)){
	irq_handlers[irq] = handler;
}

void irq_handler(registers_t regs){
	int irq = regs.err_code;
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
		char err_code[5];
		kprint("Received IRQ ");
		kprint(itoa(irq, err_code, 10));
		pic_eoi(irq);
		return;
	}
	(irq_handlers[irq])(regs);
}