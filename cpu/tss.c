#include <stdint.h>
#include "tss.h"
#include "gdt.h"
#include "x86.h"

extern const uint32_t isr_stack_top;

tss_entry_t tss = {
	.prev_tss = 0x0,
	.esp0 = 0x0,
	.ss0 = KERNEL_DS,
	.esp1 = 0x0,
	.ss1 = 0x0,
	.esp2 = 0x0,
	.ss2 = 0x0,
	.cr3 = 0x0,
	.eip = 0x0,
	.eflags = 0x0,
	.eax = 0x0,
	.ecx = 0x0,
	.edx = 0x0,
	.ebx = 0x0,
	.esp = 0x0,
	.ebp = 0x0,
	.esi = 0x0,
	.edi = 0x0,
	.es = 0x0,
	.cs = 0x0,
	.ss = 0x0,
	.ds = 0x0,
	.fs = 0x0,
	.gs = 0x0,
	.ldt = 0x0,
	.trap = 0x0,
	.iomap_base = sizeof(tss)
};

void tss_init(void){
	tss.esp0 = isr_stack_top;
	gdt_entry_t *gdt_tss = &gdt[6];
	gdt_tss->base_low = ((uintptr_t) &tss) & 0xFF;
	gdt_tss->base_middle = (((uintptr_t) &tss) >> 16) & 0xF;
	gdt_tss->base_high = (((uintptr_t) &tss) >> 24) & 0xF;
	ltr(GDT_TSS);
}