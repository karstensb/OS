#include <stdint.h>
#include "idt.h"
#include "gdt.h"
#include "x86.h"

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

void idt_init(void){
	idt[0].offset_low = ((uint32_t) &isr0) & 0xFFFF;
	idt[0].offset_high = (((uint32_t) &isr0) >> 16) & 0xFFFF;
	idt[1].offset_low = ((uint32_t) &isr1) & 0xFFFF;
	idt[1].offset_high = (((uint32_t) &isr1) >> 16) & 0xFFFF;
	idt[2].offset_low = ((uint32_t) &isr2) & 0xFFFF;
	idt[2].offset_high = (((uint32_t) &isr2) >> 16) & 0xFFFF;
	idt[3].offset_low = ((uint32_t) &isr3) & 0xFFFF;
	idt[3].offset_high = (((uint32_t) &isr3) >> 16) & 0xFFFF;
	idt[4].offset_low = ((uint32_t) &isr4) & 0xFFFF;
	idt[4].offset_high = (((uint32_t) &isr4) >> 16) & 0xFFFF;
	idt[5].offset_low = ((uint32_t) &isr5) & 0xFFFF;
	idt[5].offset_high = (((uint32_t) &isr5) >> 16) & 0xFFFF;
	idt[6].offset_low = ((uint32_t) &isr6) & 0xFFFF;
	idt[6].offset_high = (((uint32_t) &isr6) >> 16) & 0xFFFF;
	idt[7].offset_low = ((uint32_t) &isr7) & 0xFFFF;
	idt[7].offset_high = (((uint32_t) &isr7) >> 16) & 0xFFFF;
	idt[8].offset_low = ((uint32_t) &isr8) & 0xFFFF;
	idt[8].offset_high = (((uint32_t) &isr8) >> 16) & 0xFFFF;
	idt[9].offset_low = ((uint32_t) &isr9) & 0xFFFF;
	idt[9].offset_high = (((uint32_t) &isr9) >> 16) & 0xFFFF;
	idt[10].offset_low = ((uint32_t) &isr10) & 0xFFFF;
	idt[10].offset_high = (((uint32_t) &isr10) >> 16) & 0xFFFF;
	idt[11].offset_low = ((uint32_t) &isr11) & 0xFFFF;
	idt[11].offset_high = (((uint32_t) &isr11) >> 16) & 0xFFFF;
	idt[12].offset_low = ((uint32_t) &isr12) & 0xFFFF;
	idt[12].offset_high = (((uint32_t) &isr12) >> 16) & 0xFFFF;
	idt[13].offset_low = ((uint32_t) &isr13) & 0xFFFF;
	idt[13].offset_high = (((uint32_t) &isr13) >> 16) & 0xFFFF;
	idt[14].offset_low = ((uint32_t) &isr14) & 0xFFFF;
	idt[14].offset_high = (((uint32_t) &isr14) >> 16) & 0xFFFF;
	idt[15].offset_low = ((uint32_t) &isr15) & 0xFFFF;
	idt[15].offset_high = (((uint32_t) &isr15) >> 16) & 0xFFFF;
	idt[16].offset_low = ((uint32_t) &isr16) & 0xFFFF;
	idt[16].offset_high = (((uint32_t) &isr16) >> 16) & 0xFFFF;
	idt[17].offset_low = ((uint32_t) &isr17) & 0xFFFF;
	idt[17].offset_high = (((uint32_t) &isr17) >> 16) & 0xFFFF;
	idt[18].offset_low = ((uint32_t) &isr18) & 0xFFFF;
	idt[18].offset_high = (((uint32_t) &isr18) >> 16) & 0xFFFF;
	idt[19].offset_low = ((uint32_t) &isr19) & 0xFFFF;
	idt[19].offset_high = (((uint32_t) &isr19) >> 16) & 0xFFFF;
	idt[20].offset_low = ((uint32_t) &isr20) & 0xFFFF;
	idt[20].offset_high = (((uint32_t) &isr20) >> 16) & 0xFFFF;
	idt[21].offset_low = ((uint32_t) &isr21) & 0xFFFF;
	idt[21].offset_high = (((uint32_t) &isr21) >> 16) & 0xFFFF;
	idt[22].offset_low = ((uint32_t) &isr22) & 0xFFFF;
	idt[22].offset_high = (((uint32_t) &isr22) >> 16) & 0xFFFF;
	idt[23].offset_low = ((uint32_t) &isr23) & 0xFFFF;
	idt[23].offset_high = (((uint32_t) &isr23) >> 16) & 0xFFFF;
	idt[24].offset_low = ((uint32_t) &isr24) & 0xFFFF;
	idt[24].offset_high = (((uint32_t) &isr24) >> 16) & 0xFFFF;
	idt[25].offset_low = ((uint32_t) &isr25) & 0xFFFF;
	idt[25].offset_high = (((uint32_t) &isr25) >> 16) & 0xFFFF;
	idt[26].offset_low = ((uint32_t) &isr26) & 0xFFFF;
	idt[26].offset_high = (((uint32_t) &isr26) >> 16) & 0xFFFF;
	idt[27].offset_low = ((uint32_t) &isr27) & 0xFFFF;
	idt[27].offset_high = (((uint32_t) &isr27) >> 16) & 0xFFFF;
	idt[28].offset_low = ((uint32_t) &isr28) & 0xFFFF;
	idt[28].offset_high = (((uint32_t) &isr28) >> 16) & 0xFFFF;
	idt[29].offset_low = ((uint32_t) &isr29) & 0xFFFF;
	idt[29].offset_high = (((uint32_t) &isr29) >> 16) & 0xFFFF;
	idt[30].offset_low = ((uint32_t) &isr30) & 0xFFFF;
	idt[30].offset_high = (((uint32_t) &isr30) >> 16) & 0xFFFF;
	idt[31].offset_low = ((uint32_t) &isr31) & 0xFFFF;
	idt[31].offset_high = (((uint32_t) &isr31) >> 16) & 0xFFFF;

	idt[32].offset_low = ((uint32_t) &irq0) & 0xFFFF;
	idt[32].offset_high = (((uint32_t) &irq0) >> 16) & 0xFFFF;
	idt[33].offset_low = ((uint32_t) &irq1) & 0xFFFF;
	idt[33].offset_high = (((uint32_t) &irq1) >> 16) & 0xFFFF;
	idt[34].offset_low = ((uint32_t) &irq2) & 0xFFFF;
	idt[34].offset_high = (((uint32_t) &irq2) >> 16) & 0xFFFF;
	idt[35].offset_low = ((uint32_t) &irq3) & 0xFFFF;
	idt[35].offset_high = (((uint32_t) &irq3) >> 16) & 0xFFFF;
	idt[36].offset_low = ((uint32_t) &irq4) & 0xFFFF;
	idt[36].offset_high = (((uint32_t) &irq4) >> 16) & 0xFFFF;
	idt[37].offset_low = ((uint32_t) &irq5) & 0xFFFF;
	idt[37].offset_high = (((uint32_t) &irq5) >> 16) & 0xFFFF;
	idt[38].offset_low = ((uint32_t) &irq6) & 0xFFFF;
	idt[38].offset_high = (((uint32_t) &irq6) >> 16) & 0xFFFF;
	idt[39].offset_low = ((uint32_t) &irq7) & 0xFFFF;
	idt[39].offset_high = (((uint32_t) &irq7) >> 16) & 0xFFFF;
	idt[40].offset_low = ((uint32_t) &irq8) & 0xFFFF;
	idt[40].offset_high = (((uint32_t) &irq8) >> 16) & 0xFFFF;
	idt[41].offset_low = ((uint32_t) &irq9) & 0xFFFF;
	idt[41].offset_high = (((uint32_t) &irq9) >> 16) & 0xFFFF;
	idt[42].offset_low = ((uint32_t) &irq10) & 0xFFFF;
	idt[42].offset_high = (((uint32_t) &irq10) >> 16) & 0xFFFF;
	idt[43].offset_low = ((uint32_t) &irq11) & 0xFFFF;
	idt[43].offset_high = (((uint32_t) &irq11) >> 16) & 0xFFFF;
	idt[44].offset_low = ((uint32_t) &irq12) & 0xFFFF;
	idt[44].offset_high = (((uint32_t) &irq12) >> 16) & 0xFFFF;
	idt[45].offset_low = ((uint32_t) &irq13) & 0xFFFF;
	idt[45].offset_high = (((uint32_t) &irq13) >> 16) & 0xFFFF;
	idt[46].offset_low = ((uint32_t) &irq14) & 0xFFFF;
	idt[46].offset_high = (((uint32_t) &irq14) >> 16) & 0xFFFF;
	idt[47].offset_low = ((uint32_t) &irq15) & 0xFFFF;
	idt[47].offset_high = (((uint32_t) &irq15) >> 16) & 0xFFFF;

	lidt(sizeof(idt) - 1, (uint32_t) &idt);
}