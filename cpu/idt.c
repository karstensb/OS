#include "idt.h"
#include "gdt.h"
#include "x86.h"

struct idt_entry idt[256];

void idt_register_handler(uint8_t n, enum idt_type type, uint32_t handler)
{
	idt[n].offset_low = handler & 0xFFFF;
	idt[n].selector = KERNEL_CS;
	idt[n].type = type;
	idt[n].dpl = 3;
	idt[n].present = 1;
	idt[n].offset_high = (handler >> 16) & 0xFFFF;
	lidt(sizeof(idt) - 1, (uint32_t)&idt);
}
