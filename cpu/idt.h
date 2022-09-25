#pragma once

#include <stdint.h>

enum idt_type
{
	TASK_GATE = 0x5,
	INTERRUPT_16 = 0x6, /* Automatically disable/reenable Interrupts */
	TRAP_16 = 0x7,
	INTERRUPT_32 = 0xE, /* Automatically disable/reenable Interrupts */
	TRAP_32 = 0xF,
};

struct idt_entry
{
	uint16_t offset_low;
	uint16_t selector;
	uint8_t : 8;
	uint8_t type : 4;
	uint8_t : 1;
	uint8_t dpl : 2;
	uint8_t present : 1;
	uint16_t offset_high;
} __attribute__((packed));

struct idt_descriptor
{
	uint16_t size;
	uint32_t offset;
} __attribute__((packed));

struct interrupt_frame
{
	uint32_t eip;
	uint16_t cs;
	uint16_t : 16; /* padding */
	uint32_t eflags;
	/* only on cpl change*/
	uint32_t user_esp;
	uint16_t user_ss;
	uint16_t : 16; /* padding */
} __attribute__((packed));

extern struct idt_entry idt[256];

void idt_register_handler(uint8_t n, enum idt_type type, uint32_t handler);
