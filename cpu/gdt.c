#include "gdt.h"
#include "tss.h"

gdt_entry_t gdt[6] = {
	{.limit_low = 0x0000, .base_low = 0x0, .base_middle = 0x0, .access = 0x00, .granularity = 0x00, .base_high = 0x00},
	{.limit_low = 0xFFFF, .base_low = 0x0, .base_middle = 0x0, .access = 0x9A, .granularity = 0xCF, .base_high = 0xFF},
	{.limit_low = 0xFFFF, .base_low = 0x0, .base_middle = 0x0, .access = 0x92, .granularity = 0xCF, .base_high = 0xFF},
	{.limit_low = 0xFFFF, .base_low = 0x0, .base_middle = 0x0, .access = 0xFA, .granularity = 0xCF, .base_high = 0xFF},
	{.limit_low = 0xFFFF, .base_low = 0x0, .base_middle = 0x0, .access = 0xF2, .granularity = 0xCF, .base_high = 0xFF},
	{.limit_low = sizeof(tss), .base_low = 0x0, .base_middle = 0x0, .access = 0x89, .granularity = (sizeof(tss) >> 16) & 0xF, .base_high = 0x0}
};

const gdt_descriptor_t gdt_descriptor = {
	.size = sizeof(gdt) - 1,
	.offset = (uint32_t) &gdt
};