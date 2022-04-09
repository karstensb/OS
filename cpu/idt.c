#include "idt.h"
#include "util.h"

idt_gate_t idt[IDT_ENTRIES];

void set_idt_gate(int n, uint32_t handler){
	idt[n].offset_low = low_16(handler);
	idt[n].selector = KERNEL_CS;
	idt[n].zero = 0;
	idt[n].flags = 1 << 7 | INTERRUPT32;
	idt[n].offset_high = high_16(handler);
}

void set_idt_trap(int n, uint32_t handler){
	idt[n].offset_low = low_16(handler);
	idt[n].selector = KERNEL_CS;
	idt[n].zero = 0;
	idt[n].flags = 1 << 7 | TRAP_32;
	idt[n].offset_high = high_16(handler);
}

void load_idt(void){
	idt_register_t idt_descriptor;
	idt_descriptor.size = sizeof(idt) * sizeof(idt_gate_t) - 1;
	idt_descriptor.offset = (uint32_t) idt;
	asm volatile("lidt %0"::"g" (idt_descriptor));
	asm volatile("sti");
}