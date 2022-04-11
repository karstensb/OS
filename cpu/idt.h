#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#include "gdt.h"

typedef enum idt_gate_type{
	TASK_GATE = 0b0101,
	INTERRUPT_16 = 0b0110,
	TRAP_16 = 0b0111,
	INTERRUPT32 = 0b1110,
	TRAP_32 = 0b1111
}idt_gate_type_t;

typedef struct idt_gate{
	uint16_t offset_low;
	uint16_t selector;
	uint8_t  zero;
	uint8_t  flags;
	uint16_t offset_high;
}__attribute__((packed)) idt_gate_t;


typedef struct idt_register{
    uint16_t size;
    uint32_t offset;
}__attribute__((packed)) idt_register_t;

void set_idt_gate(int n, uint32_t handler);
void set_idt_trap(int n, uint32_t handler);
void load_idt(void);

#endif /* IDT_H */