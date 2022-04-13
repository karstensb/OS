#ifndef IDT_H
#define IDT_H

#include <stdint.h>

typedef enum idt_gate_type{
	TASK_GATE = 0b0101,
	INTERRUPT_16 = 0b0110,
	TRAP_16 = 0b0111,
	INTERRUPT_32 = 0b1110,
	TRAP_32 = 0b1111
}idt_gate_type_t;

typedef struct idt_entry{
	uint16_t offset_low;
	uint16_t selector;
	uint8_t  zero;
	uint8_t  flags;
	uint16_t offset_high;
}__attribute__((packed)) idt_entry_t;

typedef struct idt_descriptor{
    uint16_t size;
    uint32_t offset;
}__attribute__((packed)) idt_descriptor_t;

extern idt_entry_t idt[48];

void init_idt(void);

#endif /* IDT_H */