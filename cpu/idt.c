#include <stdint.h>
#include "idt.h"
#include "gdt.h"
#include "x86.h"

#define IDT_PRESENT (1 << 7)

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

idt_entry idt[256];

void register_isr_handler(uint8_t n, uint8_t type, void (*handler)(void)){
	idt[n].offset_low = (uint32_t)handler & 0xFFFF;
	idt[n].selector = KERNEL_CS;
	idt[n].zero = 0;
	idt[n].flags = IDT_PRESENT | type;
	idt[n].offset_high = ((uint32_t)handler >> 16) & 0xFFFF;
	lidt(sizeof(idt) - 1, (uint32_t) &idt);
}

void idt_init(void){
	register_isr_handler(0, INTERRUPT_32, &isr0);
	register_isr_handler(1, INTERRUPT_32, &isr1);
	register_isr_handler(2, INTERRUPT_32, &isr2);
	register_isr_handler(3, INTERRUPT_32, &isr3);
	register_isr_handler(4, INTERRUPT_32, &isr4);
	register_isr_handler(5, INTERRUPT_32, &isr5);
	register_isr_handler(6, INTERRUPT_32, &isr6);
	register_isr_handler(7, INTERRUPT_32, &isr7);
	register_isr_handler(8, INTERRUPT_32, &isr8);
	register_isr_handler(9, INTERRUPT_32, &isr9);
	register_isr_handler(10, INTERRUPT_32, &isr10);
	register_isr_handler(11, INTERRUPT_32, &isr11);
	register_isr_handler(12, INTERRUPT_32, &isr12);
	register_isr_handler(13, INTERRUPT_32, &isr13);
	register_isr_handler(14, INTERRUPT_32, &isr14);
	register_isr_handler(15, INTERRUPT_32, &isr15);
	register_isr_handler(16, INTERRUPT_32, &isr16);
	register_isr_handler(17, INTERRUPT_32, &isr17);
	register_isr_handler(18, INTERRUPT_32, &isr18);
	register_isr_handler(19, INTERRUPT_32, &isr19);
	register_isr_handler(20, INTERRUPT_32, &isr20);
	register_isr_handler(21, INTERRUPT_32, &isr21);
	register_isr_handler(22, INTERRUPT_32, &isr22);
	register_isr_handler(23, INTERRUPT_32, &isr23);
	register_isr_handler(24, INTERRUPT_32, &isr24);
	register_isr_handler(25, INTERRUPT_32, &isr25);
	register_isr_handler(26, INTERRUPT_32, &isr26);
	register_isr_handler(27, INTERRUPT_32, &isr27);
	register_isr_handler(28, INTERRUPT_32, &isr28);
	register_isr_handler(29, INTERRUPT_32, &isr29);
	register_isr_handler(30, INTERRUPT_32, &isr30);
	register_isr_handler(31, INTERRUPT_32, &isr31);
}