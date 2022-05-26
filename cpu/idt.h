#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define INTERRUPT_32 (0b1110)
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

extern idt_entry idt[256];

void idt_init(void);
void register_isr_handler(uint8_t n, uint8_t type, void (*handler)(void));

#endif /* IDT_H */