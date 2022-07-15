#pragma once

#include <stdint.h>

#define APIC_LVT_MASKED (1 << 16)

enum apic_regs{
	APIC_ID = 0x20,
	APIC_VERION = 0x30,
	APIC_TPR = 0x80,
	APIC_APR = 0x90,
	APIC_PPR = 0xA0,
	APIC_EOI = 0xB0,
	APIC_REMOTE_READ = 0xC0,
	APIC_LDR = 0xD0,
	APIC_DFR = 0xE0,
	APIC_SPURIOUS = 0xF0,
	APIC_ISR = 0x100,
	APIC_TMR = 0x180,
	APIC_IRR = 0x200,
	APIC_ESR = 0x280,
	APIC_INT_CMD_LOW = 0x300,
	APIC_INT_CMD_HIGH = 0x310,
	APIC_LVT_TMR = 0x320,
	APIC_LVT_THERMAL = 0x330,
	APIC_LVT_PERF = 0x340,
	APIC_LVT_LINT0 = 0x350, /* legacy 8259A PIC */
	APIC_LVT_LINT1 = 0x360, /* legacy NMI */
	APIC_LVT_ERROR = 0x370,
	APIC_TIMER_INIT = 0x380,
	APIC_TIMER_CURRENT = 0x390,
	APIC_TIMER_DIV = 0x3E0
};

void apic_write(uint32_t reg, uint32_t val);
uint32_t apic_read(uint32_t reg);
void apic_eoi(void);
