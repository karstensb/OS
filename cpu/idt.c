#include <stdint.h>
#include "idt.h"
#include "gdt.h"
#include "util.h"

extern uint32_t isr0;
extern uint32_t isr1;
extern uint32_t isr2;
extern uint32_t isr3;
extern uint32_t isr4;
extern uint32_t isr5;
extern uint32_t isr6;
extern uint32_t isr7;
extern uint32_t isr8;
extern uint32_t isr9;
extern uint32_t isr10;
extern uint32_t isr11;
extern uint32_t isr12;
extern uint32_t isr13;
extern uint32_t isr14;
extern uint32_t isr15;
extern uint32_t isr16;
extern uint32_t isr17;
extern uint32_t isr18;
extern uint32_t isr19;
extern uint32_t isr20;
extern uint32_t isr21;
extern uint32_t isr22;
extern uint32_t isr23;
extern uint32_t isr24;
extern uint32_t isr25;
extern uint32_t isr26;
extern uint32_t isr27;
extern uint32_t isr28;
extern uint32_t isr29;
extern uint32_t isr30;
extern uint32_t isr31;

extern uint32_t irq0;
extern uint32_t irq1;
extern uint32_t irq2;
extern uint32_t irq3;
extern uint32_t irq4;
extern uint32_t irq5;
extern uint32_t irq6;
extern uint32_t irq7;
extern uint32_t irq8;
extern uint32_t irq9;
extern uint32_t irq10;
extern uint32_t irq11;
extern uint32_t irq12;
extern uint32_t irq13;
extern uint32_t irq14;
extern uint32_t irq15;

idt_entry_t idt[48] = {
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | INTERRUPT_32, .offset_high = 0x0},

	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | TRAP_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | TRAP_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | TRAP_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | TRAP_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | TRAP_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | TRAP_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | TRAP_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | TRAP_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | TRAP_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | TRAP_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | TRAP_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | TRAP_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | TRAP_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | TRAP_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | TRAP_32, .offset_high = 0x0},
	{.offset_low = 0x0, .selector = KERNEL_CS, .zero = 0x0, .flags = 1 << 7 | TRAP_32, .offset_high = 0x0},
};

const idt_descriptor_t idt_descriptor = {
	.size = sizeof(idt) / sizeof(idt_entry_t) - 1,
	.offset = (uint32_t) &idt,
};

void init_idt(void){
	idt[0].offset_low = isr0 & 0xFF;
	idt[0].offset_high = (isr0 >> 16) & 0xFF;
	idt[1].offset_low = isr1 & 0xFF;
	idt[1].offset_high = (isr1 >> 16) & 0xFF;
	idt[2].offset_low = isr2 & 0xFF;
	idt[2].offset_high = (isr2 >> 16) & 0xFF;
	idt[3].offset_low = isr3 & 0xFF;
	idt[3].offset_high = (isr3 >> 16) & 0xFF;
	idt[4].offset_low = isr4 & 0xFF;
	idt[4].offset_high = (isr4 >> 16) & 0xFF;
	idt[5].offset_low = isr5 & 0xFF;
	idt[5].offset_high = (isr5 >> 16) & 0xFF;
	idt[6].offset_low = isr6 & 0xFF;
	idt[6].offset_high = (isr6 >> 16) & 0xFF;
	idt[7].offset_low = isr7 & 0xFF;
	idt[7].offset_high = (isr7 >> 16) & 0xFF;
	idt[8].offset_low = isr8 & 0xFF;
	idt[8].offset_high = (isr8 >> 16) & 0xFF;
	idt[9].offset_low = isr9 & 0xFF;
	idt[9].offset_high = (isr9 >> 16) & 0xFF;
	idt[10].offset_low = isr10 & 0xFF;
	idt[10].offset_high = (isr10 >> 16) & 0xFF;
	idt[11].offset_low = isr11 & 0xFF;
	idt[11].offset_high = (isr11 >> 16) & 0xFF;
	idt[12].offset_low = isr12 & 0xFF;
	idt[12].offset_high = (isr12 >> 16) & 0xFF;
	idt[13].offset_low = isr13 & 0xFF;
	idt[13].offset_high = (isr13 >> 16) & 0xFF;
	idt[14].offset_low = isr14 & 0xFF;
	idt[14].offset_high = (isr14 >> 16) & 0xFF;
	idt[15].offset_low = isr15 & 0xFF;
	idt[15].offset_high = (isr15 >> 16) & 0xFF;
	idt[16].offset_low = isr16 & 0xFF;
	idt[16].offset_high = (isr16 >> 16) & 0xFF;
	idt[17].offset_low = isr17 & 0xFF;
	idt[17].offset_high = (isr17 >> 16) & 0xFF;
	idt[18].offset_low = isr18 & 0xFF;
	idt[18].offset_high = (isr18 >> 16) & 0xFF;
	idt[19].offset_low = isr19 & 0xFF;
	idt[19].offset_high = (isr19 >> 16) & 0xFF;
	idt[20].offset_low = isr20 & 0xFF;
	idt[20].offset_high = (isr20 >> 16) & 0xFF;
	idt[21].offset_low = isr21 & 0xFF;
	idt[21].offset_high = (isr21 >> 16) & 0xFF;
	idt[22].offset_low = isr22 & 0xFF;
	idt[22].offset_high = (isr22 >> 16) & 0xFF;
	idt[23].offset_low = isr23 & 0xFF;
	idt[23].offset_high = (isr23 >> 16) & 0xFF;
	idt[24].offset_low = isr24 & 0xFF;
	idt[24].offset_high = (isr24 >> 16) & 0xFF;
	idt[25].offset_low = isr25 & 0xFF;
	idt[25].offset_high = (isr25 >> 16) & 0xFF;
	idt[26].offset_low = isr26 & 0xFF;
	idt[26].offset_high = (isr26 >> 16) & 0xFF;
	idt[27].offset_low = isr27 & 0xFF;
	idt[27].offset_high = (isr27 >> 16) & 0xFF;
	idt[28].offset_low = isr28 & 0xFF;
	idt[28].offset_high = (isr28 >> 16) & 0xFF;
	idt[29].offset_low = isr29 & 0xFF;
	idt[29].offset_high = (isr29 >> 16) & 0xFF;
	idt[30].offset_low = isr30 & 0xFF;
	idt[30].offset_high = (isr30 >> 16) & 0xFF;
	idt[31].offset_low = isr31 & 0xFF;
	idt[31].offset_high = (isr31 >> 16) & 0xFF;

	idt[32].offset_low = irq0 & 0xFF;
	idt[32].offset_high = (irq0 >> 16) & 0xFF;
	idt[33].offset_low = irq1 & 0xFF;
	idt[33].offset_high = (irq1 >> 16) & 0xFF;
	idt[34].offset_low = irq2 & 0xFF;
	idt[34].offset_high = (irq2 >> 16) & 0xFF;
	idt[35].offset_low = irq3 & 0xFF;
	idt[35].offset_high = (irq3 >> 16) & 0xFF;
	idt[36].offset_low = irq4 & 0xFF;
	idt[36].offset_high = (irq4 >> 16) & 0xFF;
	idt[37].offset_low = irq5 & 0xFF;
	idt[37].offset_high = (irq5 >> 16) & 0xFF;
	idt[38].offset_low = irq6 & 0xFF;
	idt[38].offset_high = (irq6 >> 16) & 0xFF;
	idt[39].offset_low = irq7 & 0xFF;
	idt[39].offset_high = (irq7 >> 16) & 0xFF;
	idt[40].offset_low = irq8 & 0xFF;
	idt[40].offset_high = (irq8 >> 16) & 0xFF;
	idt[41].offset_low = irq9 & 0xFF;
	idt[41].offset_high = (irq9 >> 16) & 0xFF;
	idt[42].offset_low = irq10 & 0xFF;
	idt[42].offset_high = (irq10 >> 16) & 0xFF;
	idt[43].offset_low = irq11 & 0xFF;
	idt[43].offset_high = (irq11 >> 16) & 0xFF;
	idt[44].offset_low = irq12 & 0xFF;
	idt[44].offset_high = (irq12 >> 16) & 0xFF;
	idt[45].offset_low = irq13 & 0xFF;
	idt[45].offset_high = (irq13 >> 16) & 0xFF;
	idt[46].offset_low = irq14 & 0xFF;
	idt[46].offset_high = (irq14 >> 16) & 0xFF;
	idt[47].offset_low = irq15 & 0xFF;
	idt[47].offset_high = (irq15 >> 16) & 0xFF;

	lidt(idt_descriptor.size, idt_descriptor.offset);
}