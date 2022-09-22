#include "apic.h"
#include "idt.h"
#include "page.h"
#include "x86.h"
#include "kernel/v_malloc.h"
#include "util/unused.h"

#define APIC_MSR (0x1B)
#define APIC_BASE (0xFEE00000)

enum lapic_regs
{
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

static void apic_write(enum apic_regs reg, uint32_t val)
{
	*((uint32_t *)(apic_base + reg)) = val;
}

static uint32_t apic_read(enum apic_regs reg)
{
	return *((uint32_t *)(apic_base + reg));
}

void apic_eoi(void)
{
	apic_write(APIC_EOI, 0);
}

__attribute__((interrupt)) static void apic_spurious(UNUSED struct interrupt_frame *frame)
{
	apic_eoi();
}

// TODO:
void ioapic_init(void)
{
	return;
}

void apic_init(void)
{
	/* Note: the legacy 8259A PIC is not initialized (remmapped and masked)
	 * because LINT0 on the APIC will be masked anyway, preventing any
	 * signal from the legacy PIC to reach the cpu */

	apic_base = alloc_pages(4096);
	pg_map((void *)0xFEE00000, apic_base, PG_CACHE_DISABLE);
	pg_used((void *)0xFEE00000);

	ioapic_init();

	/* mask all apic interrupts */
	apic_write(APIC_LVT_TMR, APIC_LVT_MASKED);
	apic_write(APIC_LVT_THERMAL, APIC_LVT_MASKED);
	apic_write(APIC_LVT_PERF, APIC_LVT_MASKED);
	apic_write(APIC_LVT_LINT0, APIC_LVT_MASKED);
	/* leave LINT1 (legacy nmi) as configured by the BIOS */
	apic_write(APIC_LVT_ERROR, APIC_LVT_MASKED);

	/* set the spurious interrupt vector */
	idt_register_handler(0xFF, TRAP_32, (uint32_t)&apic_spurious);
	apic_write(APIC_SPURIOUS, (1 << 8) | 0xFF);

	/* enable the local APIC */
	uint32_t high, low;
	rdmsr(APIC_MSR, &low, &high);
	wrmsr(APIC_MSR, low | (1 << 11), high);
}
