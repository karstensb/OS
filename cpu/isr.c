#include <stdnoreturn.h>
#include "isr.h"
#include "idt.h"
#include "../drivers/screen.h"
#include "../libc/string.h"

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();


void isr_install(){
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
	kprint(err_msg[regs.err_code]);
	kprint("\nCode: 0x");
	char err_code[5];
	kprint(itoa(regs.err_code, err_code, 16));
halt:	
	asm volatile("cli");
	asm volatile("hlt");
	asm volatile("jmp $-1");
	goto halt;
}