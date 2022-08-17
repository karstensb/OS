#include <stdnoreturn.h>
#include <stdbool.h>
#include <stdint.h>
#include "isr.h"
#include "idt.h"
#include "x86.h"
#include "drivers/screen.h"
#include "util/string.h"
#include "util/panic.h"

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

void isr_init(void){
	idt_register_handler(0, INTERRUPT_32, (uint32_t) &isr0);
	idt_register_handler(1, INTERRUPT_32, (uint32_t) &isr1);
	idt_register_handler(2, INTERRUPT_32, (uint32_t) &isr2);
	idt_register_handler(3, INTERRUPT_32, (uint32_t) &isr3);
	idt_register_handler(4, INTERRUPT_32, (uint32_t) &isr4);
	idt_register_handler(5, INTERRUPT_32, (uint32_t) &isr5);
	idt_register_handler(6, INTERRUPT_32, (uint32_t) &isr6);
	idt_register_handler(7, INTERRUPT_32, (uint32_t) &isr7);
	idt_register_handler(8, INTERRUPT_32, (uint32_t) &isr8);
	idt_register_handler(9, INTERRUPT_32, (uint32_t) &isr9);
	idt_register_handler(10, INTERRUPT_32, (uint32_t) &isr10);
	idt_register_handler(11, INTERRUPT_32, (uint32_t) &isr11);
	idt_register_handler(12, INTERRUPT_32, (uint32_t) &isr12);
	idt_register_handler(13, INTERRUPT_32, (uint32_t) &isr13);
	idt_register_handler(14, INTERRUPT_32, (uint32_t) &isr14);
	idt_register_handler(15, INTERRUPT_32, (uint32_t) &isr15);
	idt_register_handler(16, INTERRUPT_32, (uint32_t) &isr16);
	idt_register_handler(17, INTERRUPT_32, (uint32_t) &isr17);
	idt_register_handler(18, INTERRUPT_32, (uint32_t) &isr18);
	idt_register_handler(19, INTERRUPT_32, (uint32_t) &isr19);
	idt_register_handler(20, INTERRUPT_32, (uint32_t) &isr20);
	idt_register_handler(21, INTERRUPT_32, (uint32_t) &isr21);
	idt_register_handler(22, INTERRUPT_32, (uint32_t) &isr22);
	idt_register_handler(23, INTERRUPT_32, (uint32_t) &isr23);
	idt_register_handler(24, INTERRUPT_32, (uint32_t) &isr24);
	idt_register_handler(25, INTERRUPT_32, (uint32_t) &isr25);
	idt_register_handler(26, INTERRUPT_32, (uint32_t) &isr26);
	idt_register_handler(27, INTERRUPT_32, (uint32_t) &isr27);
	idt_register_handler(28, INTERRUPT_32, (uint32_t) &isr28);
	idt_register_handler(29, INTERRUPT_32, (uint32_t) &isr29);
	idt_register_handler(30, INTERRUPT_32, (uint32_t) &isr30);
	idt_register_handler(31, INTERRUPT_32, (uint32_t) &isr31);
}

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

struct registers{
	uint16_t ds;
	uint16_t _padding0;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t int_no;
	/* sometimes pushed by hardware, otherwise manually pushed */
	uint32_t err_code;
	/* pushed by hardware */
	uint32_t eip;
	uint16_t cs;
	uint16_t _padding1;
	uint32_t eflags;
	/* only on cpl change*/
	uint32_t user_esp;
	uint16_t user_ss;
	uint16_t _padding2;
}__attribute__((packed)) registers;

noreturn void isr_handler(struct registers *regs){
	clear_screen(0);
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
