#pragma once

#include <stdint.h>
#include "gdt.h"
#include "idt.h"

static inline void cli(void)
{
	asm("cli");
}

static inline void sti(void)
{
	asm("sti");
}

static inline void hlt(void)
{
	asm("hlt");
}

static inline uint8_t inb(uint16_t port)
{
	uint8_t result;
	asm volatile("inb %%dx, %%al"
				 : "=a"(result)
				 : "d"(port));
	return result;
}

static inline uint16_t inw(uint16_t port)
{
	uint16_t result;
	asm volatile("inw %%dx, %%ax"
				 : "=a"(result)
				 : "d"(port));
	return result;
}

static inline uint32_t inl(uint16_t port)
{
	uint32_t result;
	asm volatile("inl %%dx, %%eax"
				 : "=a"(result)
				 : "d"(port));
	return result;
}

static inline void outb(uint16_t port, uint8_t data)
{
	asm("outb %%al, %%dx"
		:
		: "a"(data), "d"(port));
}

static inline void outw(uint16_t port, uint16_t data)
{
	asm("outw %%ax, %%dx"
		:
		: "a"(data), "d"(port));
}

static inline void outl(uint16_t port, uint32_t data)
{
	asm("outl %%eax, %%dx"
		:
		: "a"(data), "d"(port));
}

static inline void lgdt(uint16_t size, uint32_t offset)
{
	struct gdt_descriptor gdt_descr;
	gdt_descr.size = size;
	gdt_descr.offset = offset;
	asm("lgdt (%0)"
		:
		: "r"(&gdt_descr));
}

static inline void lidt(uint16_t size, uint32_t offset)
{
	struct idt_descriptor idt_descr;
	idt_descr.size = size;
	idt_descr.offset = offset;
	asm("lidt (%0)"
		:
		: "r"(&idt_descr));
}

static inline void ltr(uint16_t selector)
{
	asm("ltr %0"
		:
		: "r"(selector));
}

static inline void wrmsr(uint32_t msr, uint32_t low, uint32_t high)
{
	asm("wrmsr"
		:
		: "c"(msr), "a"(low), "d"(high));
}

static inline void rdmsr(uint32_t msr, uint32_t *low, uint32_t *high)
{
	asm("rdmsr"
		: "=a"(*low), "=d"(*high)
		: "c"(msr));
}

static inline uint32_t rcr2(void)
{
	uint32_t cr2;
	asm("movl %%cr2, %0"
		: "=r"(cr2));
	return cr2;
}

static inline void invlpg(volatile void *addr)
{
	asm("invlpg (%0)"
		:
		: "r"((uint32_t)addr));
}
