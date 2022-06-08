#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define INTERRUPT_32 (0b1110) /* Automatically disable/reenable Interrupts */
#define TRAP_32 (0b1111)

typedef struct idt_entry{
	uint16_t offset_low;
	uint16_t selector;
	uint8_t  zero;
	uint8_t  flags;
	uint16_t offset_high;
}__attribute__((packed)) idt_entry;

typedef struct idt_descriptor{
    uint16_t size;
    uint32_t offset;
}__attribute__((packed)) idt_descriptor;

struct interrupt_frame{
	uint32_t eip;
	uint16_t cs;
	uint16_t _padding1;
	uint32_t eflags;
	/* only on cpl change*/
	uint32_t user_esp;
	uint16_t user_ss;
	uint16_t _padding0;
}__attribute__((packed));

extern idt_entry idt[256];

void idt_register_handler(uint8_t n, uint8_t type, uint32_t handler);

#endif /* IDT_H */