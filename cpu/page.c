#include <stdbool.h>
#include <stdalign.h>
#include "page.h"
#include "x86.h"
#include "kernel/multiboot.h"
#include "util/string.h"
#include "util/panic.h"

volatile alignas(4096) uint32_t page_dir[1024];

/* bitmap of physical memory (pages) */
static uint8_t page_map[0x20000];
/* ram size in bytes */
static uint32_t mem_max;
/* pointer to the first free physical page */
static uint32_t prev_index = 0;

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

void pg_map(void *phys, void *virt, uint32_t flags)
{
	phys = (void *)((uint32_t)phys & 0xFFFFF000);
	virt = (void *)((uint32_t)virt & 0xFFFFF000);
	uint32_t dir_index = pg_dir_index(virt);
	uint32_t tb_index = pg_tb_index(virt);
	bool new_table; /* is a new table allocated */

	flags |= PG_PRESENT;
	if (!page_dir[dir_index])
	{
		page_dir[dir_index] = (uint32_t)pg_alloc() | flags;
		new_table = true;
	}
	else
	{
		page_dir[dir_index] |= flags;
		new_table = false;
	}

	volatile uint32_t *page_tb = ((volatile uint32_t *)0xFFC00000) + (1024 * dir_index);
	/* clear the page table if it was newly allocated */
	if (new_table)
	{
		invlpg(page_tb);
		volatile_memset(page_tb, 0, 4096);
	}
	page_tb[tb_index] = (uint32_t)phys | flags;
	invlpg(virt);
}

void pg_unmap(void *virt)
{
	virt = (void *)((uint32_t)virt & 0xFFFFF000);
	uint32_t dir_index = pg_dir_index(virt);
	uint32_t tb_index = pg_tb_index(virt);

	volatile uint32_t *page_tb = ((volatile uint32_t *)0xFFC00000) + (1024 * dir_index);
	page_tb[tb_index] = 0;
	invlpg(virt);

	uint32_t total = 0;
	for (int i = 0; i < 1024; ++i)
	{
		total += page_tb[i];
	}
	if (total != 0)
	{
		pg_free((void *)(page_dir[dir_index] & 0xFFFFF000));
		page_dir[dir_index] = 0;
		invlpg(page_tb);
	}
}

void pg_init(void)
{
	struct mbi_tag_mmap *mmap_tag = mbi_get_tag(MBI_TAG_MMAP);
	/* mmap_tag->size includes the tag header which has to be subtracted */
	int mbi_mmap_count = (mmap_tag->size - sizeof(struct mbi_tag_mmap)) / sizeof(struct mbi_mmap_entry);

	/* find the maximum physical address */
	for (int i = 0; i < mbi_mmap_count; ++i)
	{
		uint32_t addr = (uint32_t)mmap_tag->entries[i].base_addr + mmap_tag->entries[i].length;
		if (addr > mem_max && mmap_tag->entries[i].type == 1)
		{
			mem_max = addr;
		}
	}

	/* mark all physical pages as used */
	memset(page_map, ~0, sizeof(page_map));

	/* now mark free pages as free */
	for (int i = 0; i < mbi_mmap_count; ++i)
	{
		if (mmap_tag->entries[i].type == 1)
		{
			for (void *addr = (void *)(uint32_t)mmap_tag->entries[i].base_addr;
				 addr < (void *)(uint32_t)mmap_tag->entries[i].base_addr + mmap_tag->entries[i].length;
				 addr += 4096)
			{
				if (addr < ((void *)mbi + mbi->total_size) - KERNEL_BASE)
				{
					continue;
				}
				pg_free(addr);
			}
		}
	}
}

void *pg_alloc(void)
{
	for (uint32_t index = prev_index; index < mem_max / 4096 / 8; ++index)
	{
		/* if at least one bit isn't set */
		if (~page_map[index] & 0xFF)
		{
			int map_bit = 0;
			while (!((~page_map[index] >> map_bit) & 0x1))
			{
				++map_bit;
			}
			prev_index = index;
			void *addr = (void *)(index * 4096 * 8 + map_bit * 4096);
			pg_used(addr);
			return addr;
		}
	}
	panic("out of memory");
}

void pg_free(void *addr)
{
	if (addr > (void *)mem_max)
	{
		return;
	}
	uint32_t map_index = (uint32_t)addr / 4096 / 8;
	uint32_t map_bit = (uint32_t)addr / 4096 % 8;

	page_map[map_index] &= ~(1 << map_bit);
	prev_index = map_index < prev_index ? map_index : prev_index;
}

void pg_used(void *addr)
{
	uint32_t map_index = (uint32_t)addr / 4096 / 8;
	uint32_t map_bit = (uint32_t)addr / 4096 % 8;

	page_map[map_index] |= 1 << map_bit;
}
