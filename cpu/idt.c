#include "idt.h"
#include "gdt.h"
#include "x86.h"

#define IDT_PRESENT (1 << 7)

struct idt_entry idt[256];

void idt_register_handler(uint8_t n, uint8_t type, uint32_t handler)
{
	idt[n].offset_low = handler & 0xFFFF;
	idt[n].selector = KERNEL_CS;
	idt[n].zero = 0;
	idt[n].flags = IDT_PRESENT | type;
	idt[n].offset_high = (handler >> 16) & 0xFFFF;
	lidt(sizeof(idt) - 1, (uint32_t)&idt);
}
