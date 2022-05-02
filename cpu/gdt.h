#ifndef GDT_H
#define GDT_H

#include <stdint.h>

#define KERNEL_CS (sizeof(gdt_entry) * 1)
#define KERNEL_DS (sizeof(gdt_entry) * 2)
#define USER_CS (sizeof(gdt_entry) * 3)
#define USER_DS (sizeof(gdt_entry) * 4)
#define GDT_TSS (sizeof(gdt_entry) * 5)

typedef struct gdt_entry{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__((packed)) gdt_entry;

typedef struct gdt_descriptor{
	uint16_t size;
	uint32_t offset;
} __attribute__((packed)) gdt_descriptor;

extern gdt_entry gdt[6];

#endif /* GDT_H */