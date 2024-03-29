#include <stdint.h>
#include "ioapic.h"
#include "page.h"
#include "kernel/acpi.h"
#include "kernel/acpi_tables.h"
#include "kernel/v_malloc.h"

enum ioapic_regs
{
	IOAPICID = 0x0,
	IOAPICVER = 0x1,
	IOAPICARB = 0x2,
	IOREDTBL = 0x10 /* plus the table entry number * 2 */
};

struct madt_entry
{
	uint8_t type;
	uint8_t length;
} __attribute__((packed));

enum madt_types
{
	LAPIC = 0,
	IOAPIC = 1,
	IOAPIC_SRC_ORIDE = 2,
	IOAPIC_NMI_SRC = 3,
	LAPIC_NMI = 4,
	LAPIC_ADDR_ORIDE = 5,
	LAPIC_X2 = 9
};

static volatile void *ioapic_base;
static volatile uint8_t *ioapic_regsel;
static volatile uint32_t *ioapic_reg;

static void ioapic_write(enum ioapic_regs reg, uint32_t val)
{
	*ioapic_regsel = (uint8_t)reg;
	*ioapic_reg = val;
}

static uint32_t ioapic_read(enum ioapic_regs reg)
{
	*ioapic_regsel = (uint8_t)reg;
	return *ioapic_reg;
}

void ioapic_init(void)
{
	void *ioapic_phys = NULL;
	struct madt *madt = (struct madt *)acpi_get_table("APIC");
	struct madt_entry *cur = (struct madt_entry *)madt->devices;

	/* loop over the apic entries to find ioapic (type 1) */
	for (;
		 (char *)cur + cur->length < (char *)madt + madt->header.length;
		 cur = (struct madt_entry *)((char *)cur + cur->length))
	{
		/* the ioapic base address is at offset 4 */
		if (cur->type == IOAPIC)
		{
			uint32_t *field = (uint32_t *)((char *)cur + 4);
			ioapic_phys = (void *)*field;
		}
	}

	/* placeholder until a sophisticated system is implemented */
	#include "util/panic.h"
	if (!ioapic_phys)
	{
		panic("Couldn't find an IOAPIC");
	}

	/* map the registers into memory, considering the page offset (%4096) */
	ioapic_base = alloc_pages(4) + (size_t)ioapic_phys % 4096;
	ioapic_regsel = ioapic_base;
	ioapic_reg = ioapic_base + 0x10;
	pg_map(ioapic_phys, (void *)ioapic_base, PG_CACHE_DISABLE);

	return;
}
