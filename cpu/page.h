#pragma once

#include <stdint.h>

#define KERNEL_BASE (0xE0000000)

enum pg_flags
{
	PG_PRESENT = 0x1,
	PG_READ_WRITE = 0x2,
	PG_USER_SUPER = 0x4,
	PG_WRITE_THROUGH = 0x8,
	PG_CACHE_DISABLE = 0x10,
	PG_PAT = 0x80,
	PG_GLOBAL = 0x100
};

/* maps a single physical page to a virtual page (lower 12 bits are ignored) */
void pg_map(void *phys, void *virt, uint32_t flags);
void pg_unmap(void *virt);

void pg_init(void);

/* allocate/free a single page */
void *pg_alloc(void);
void pg_free(void *addr);

/* mark a single page as used, e.g. for mmio */
void pg_used(void *addr);
