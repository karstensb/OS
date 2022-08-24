#pragma once

#include <stdint.h>

#define KERNEL_BASE (0xE0000000)

#define PG_PRESENT (1 << 0)
#define PG_WRITE (1 << 1)
#define PG_USER (1 << 2)
#define PG_CACHE_DISABLE (1 << 4)

static inline uint32_t pg_dir_index(void *addr)
{
	return (((uint32_t)addr) >> 22) & 0x3FF;
}

static inline uint32_t pg_tb_index(void *addr)
{
	return (((uint32_t)addr) >> 12) & 0x3FF;
}

static inline uint32_t pg_offset(void *addr)
{
	return ((uint32_t)addr) & 0xFFF;
}

/* maps a single physical page to a virtual page (lower 12 bits are ignored) */
void pg_map(void *phys, void *virt, uint32_t flags);
void pg_unmap(void *addr);

void pg_init(void);

/* allocate/free a single page */
void *pg_alloc(void);
void pg_free(void *addr);

/* mark a single page as used, e.g. for mmio */
void pg_used(void *addr);
