#include "pic.h"
#include "util.h"

#define PIC1_CMD (0x20)
#define PIC1_DATA (0x21)
#define PIC2_CMD (0xA0)
#define PIC2_DATA (0xA1)

#define ICW1_ICW4 (0x01)
#define ICW1_INIT (0x10)

#define ICW4_8086 (0x01)

#define PIC_EOI (0x20)

#define PIC_READ_ISR (0x0b)


void init_pic(void){
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

	outb(PIC1_DATA, 0x0);
	outb(PIC2_DATA, 0x0);
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

	cli();
	if (irq < 8)
		port = PIC1_DATA;
	else{
		port = PIC2_DATA;
		irq -= 8;
	}
	mask = inb(port);
	outb(port, mask | (1 << irq));
	sti();
}

void irq_disable(uint8_t irq){
	uint8_t mask;
	uint16_t port;

	cli();
	if (irq < 8)
		port = PIC1_DATA;
	else{
		port = PIC2_DATA;
		irq -= 8;
	}
	mask = inb(port);
	outb(port, mask | ~(1 << irq));
	sti();
}

uint16_t pic_get_isr(void){
	outb(PIC1_CMD, PIC_READ_ISR);
	outb(PIC2_CMD, PIC_READ_ISR);
	return (inb(PIC2_CMD) << 8) | inb(PIC1_CMD);
}

void pic_disable(void){
	outb(PIC1_DATA, 0xff);
	outb(PIC2_DATA, 0xff);
}