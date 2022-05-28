#include "pic.h"
#include "idt.h"
#include "x86.h"

#define PIC1_CMD (0x20)
#define PIC1_DATA (0x21)
#define PIC2_CMD (0xA0)
#define PIC2_DATA (0xA1)

#define ICW1_ICW4 (0x01)
#define ICW1_INIT (0x10)

#define ICW4_8086 (0x01)

#define PIC_EOI (0x20)

#define PIC_READ_ISR (0x0b)

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

void pic_init(void){
	outb(PIC1_CMD, ICW1_INIT | ICW1_ICW4);
	outb(PIC2_CMD, ICW1_INIT | ICW1_ICW4);

 	/* remap PIC */
	outb(PIC1_DATA, 0x20);
	outb(PIC2_DATA, 0x28);

	/* master/slave mapping */
	outb(PIC1_DATA, 0x04);
	outb(PIC2_DATA, 0x02);

	outb(PIC1_DATA, ICW4_8086);
	outb(PIC2_DATA, ICW4_8086);

	outb(PIC1_DATA, 0xFF);
	outb(PIC2_DATA, 0xFF);

	idt_register_handler(32, TRAP_32, (uint32_t) &irq0);
	idt_register_handler(33, TRAP_32, (uint32_t) &irq1);
	idt_register_handler(34, TRAP_32, (uint32_t) &irq2);
	idt_register_handler(35, TRAP_32, (uint32_t) &irq3);
	idt_register_handler(36, TRAP_32, (uint32_t) &irq4);
	idt_register_handler(37, TRAP_32, (uint32_t) &irq5);
	idt_register_handler(38, TRAP_32, (uint32_t) &irq6);
	idt_register_handler(39, TRAP_32, (uint32_t) &irq7);
	idt_register_handler(40, TRAP_32, (uint32_t) &irq8);
	idt_register_handler(41, TRAP_32, (uint32_t) &irq9);
	idt_register_handler(42, TRAP_32, (uint32_t) &irq10);
	idt_register_handler(43, TRAP_32, (uint32_t) &irq11);
	idt_register_handler(44, TRAP_32, (uint32_t) &irq12);
	idt_register_handler(45, TRAP_32, (uint32_t) &irq13);
	idt_register_handler(46, TRAP_32, (uint32_t) &irq14);
	idt_register_handler(47, TRAP_32, (uint32_t) &irq15);
}

void pic_eoi(uint8_t irq){
	if(irq >= 8){
		outb(PIC2_CMD, PIC_EOI);
	}
	outb(PIC1_CMD, PIC_EOI);
}

void irq_enable(uint8_t irq){
	uint8_t mask;
	uint16_t port;

	if (irq < 8)
		port = PIC1_DATA;
	else{
		port = PIC2_DATA;
		irq -= 8;
	}
	mask = inb(port);
	outb(port, mask & ~(1 << irq));
}

void irq_disable(uint8_t irq){
	uint8_t mask;
	uint16_t port;

	if (irq < 8)
		port = PIC1_DATA;
	else{
		port = PIC2_DATA;
		irq -= 8;
	}
	mask = inb(port);
	outb(port, mask | (1 << irq));
}

uint16_t pic_get_isr(void){
	outb(PIC1_CMD, PIC_READ_ISR);
	outb(PIC2_CMD, PIC_READ_ISR);
	return (inb(PIC2_CMD) << 8) | inb(PIC1_CMD);
}

void pic_disable(void){
	outb(PIC1_DATA, 0xFF);
	outb(PIC2_DATA, 0xFF);
}