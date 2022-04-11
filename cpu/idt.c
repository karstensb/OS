#include "idt.h"
#include "util.h"

#define IDT_ENTRIES (256)

static idt_gate_t idt[IDT_ENTRIES];

void set_idt_gate(int n, uint32_t handler){
	idt[n].offset_low = (uint16_t) handler & 0xFFFF;
	idt[n].selector = KERNEL_CS;
	idt[n].zero = 0;
	idt[n].flags = 1 << 7 | INTERRUPT32;
	idt[n].offset_high = (uint16_t) (handler >> 16) & 0xFFFF;
}

void set_idt_trap(int n, uint32_t handler){
	idt[n].offset_low = (uint16_t) handler & 0xFFFF;
	idt[n].selector = KERNEL_CS;
	idt[n].zero = 0;
	idt[n].flags = 1 << 7 | TRAP_32;
	idt[n].offset_high = (uint16_t) (handler >> 16) & 0xFFFF;
}

void load_idt(void){
	idt_register_t idt_descriptor;
	idt_descriptor.size = sizeof(idt) * sizeof(idt_gate_t) - 1;
	idt_descriptor.offset = (uint32_t) idt;
	asm volatile("lidt %0"::"g" (idt_descriptor));
	sti();
}