#include "apic.h"
#include "idt.h"
#include "page.h"
#include "x86.h"
#include "util/util.h"
#include "drivers/screen.h"

#define APIC_MSR (0x1B)
#define APIC_BASE (0xFEE00000)

void apic_write(uint32_t reg, uint32_t val){
	*((uint32_t *) (APIC_BASE + reg)) = val;
}

uint32_t apic_read(uint32_t reg){
	return *((uint32_t *) (APIC_BASE + reg));
}

void apic_eoi(void){
	apic_write(APIC_EOI, 0);
}

__attribute__((interrupt))
static void apic_spurious(struct interrupt_frame *frame){
	UNUSED(frame);
	apic_eoi();
}

void apic_init(void){
	/* Note: the legacy 8259A PIC is not initialized (remmapped and masked)
	 * because LINT0 on the APIC will be masked anyway, preventing any
	 * signal from the legacy PIC to reach the cpu */

	pg_map((void *) APIC_BASE, (void *) APIC_BASE, PG_PRESENT);

	/* mask all apic interrupts */
	apic_write(APIC_LVT_TMR, APIC_LVT_MASKED);
	apic_write(APIC_LVT_THERMAL, APIC_LVT_MASKED);
	apic_write(APIC_LVT_PERF, APIC_LVT_MASKED);
	apic_write(APIC_LVT_LINT0, APIC_LVT_MASKED);
	apic_write(APIC_LVT_LINT1, APIC_LVT_MASKED);
	apic_write(APIC_LVT_ERROR, APIC_LVT_MASKED);

	/* set the spurious interrupt vector */
	idt_register_handler(0xFF, TRAP_32, (uint32_t) &apic_spurious);
	apic_write(APIC_SPURIOUS, (1 << 8) | 0xFF);

	/* enable the local APIC */
	uint32_t high, low;
	rdmsr(APIC_MSR, &low, &high);
	wrmsr(APIC_MSR, low | (1 << 11), high);
}