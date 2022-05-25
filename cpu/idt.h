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

void idt_init(void);

#endif /* IDT_H */