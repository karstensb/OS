#include <limits.h>
#include "page.h"
#include "x86.h"
#include "kernel/multiboot.h"
#include "util/string.h"
#include "util/panic.h"

//TODO: self referential page table
uint32_t page_dir[1024] __attribute__((aligned(4096)));
uint32_t page_table[1024] __attribute__((aligned(4096)));
extern uint32_t page_table_0[1024] __attribute__((aligned(4096)));


/* bitmap of physical memory (pages) */
static uint8_t page_map[0x20000];
/* ram size in bytes */
static uint32_t mem_max;
/* pointer to the first free physical page */
static uint32_t prev_index = 0;

void pg_map(void *phys, void *virt, uint32_t flags){
	uint32_t dir_index = pg_dir_index(virt);
	uint32_t tb_index = pg_tb_index(virt);

	flags |= PG_PRESENT;
	if(!page_dir[dir_index]){
		page_dir[dir_index] = (uint32_t) pg_alloc() | flags;
	}else{
		page_dir[dir_index] |= flags;
	}

	/* map the to-be-edited page table to page_table 
	 * This way the page tables don't occupy much virtual memory and handling
	 * is a lot easier. page_table_0 contains page_table and is always mapped 
	 * so other page tables can be mapped at all */
	page_table_0[pg_tb_index(page_table)] = ((uint32_t) page_dir[dir_index]) | PG_PRESENT;
	invlpg(page_table);
	page_table[tb_index] = ((uint32_t) phys & 0xFFFFF000) | flags;
	invlpg(virt);
}

void pg_unmap(void *addr){
	uint32_t dir_index = pg_dir_index(addr);
	uint32_t tb_index = pg_tb_index(addr);

	/* see above in pg_map */
	page_table_0[pg_tb_index(page_table)] = ((uint32_t) page_dir[dir_index]) | PG_PRESENT;
	invlpg(page_table);
	page_table[tb_index] = 0;
	invlpg(addr);
}

void pg_init(void){
	struct mbi_tag_mmap *mmap_tag = mbi_get_tag(MBI_TAG_MMAP);
	/* mmap_tag->size includes the tag header which has to be subtracted */
	int mbi_mmap_count = (mmap_tag->size - sizeof(struct mbi_tag_mmap)) / sizeof(struct mbi_mmap_entry);

	/* find the maximum physical address */
	for(int i = 0; i < mbi_mmap_count; ++i){
		uint32_t addr = (uint32_t) mmap_tag->entries[i].base_addr+mmap_tag->entries[i].length;
		if(addr > mem_max && mmap_tag->entries[i].type == 1){
			mem_max = addr;
		}
	}

	/* mark all physical pages as used */
	memset(page_map, ~0, sizeof(page_map));

	/* now mark free pages as free */
	for(int i = 0; i < mbi_mmap_count; ++i){
		if(mmap_tag->entries[i].type == 1){
			for(void *addr = (void *) (uint32_t) mmap_tag->entries[i].base_addr;
				addr < (void *) (uint32_t) mmap_tag->entries[i].base_addr + mmap_tag->entries[i].length;
				addr += 4096){
				if(addr < ((void *) mbi + mbi->total_size) - KERNEL_BASE){
					continue;
				}
				pg_free(addr);
			}
		}
	}
}

void *pg_alloc(void){
	for(uint32_t index = prev_index; index < mem_max/4096/8; ++index){
		/* if at least one bit isn't set */
		if(~page_map[index] & 0xFF){
			int map_bit = 0;
			while(!((~page_map[index] >> map_bit) & 0x1)){
				++map_bit;
			}
			prev_index = index;
			void * addr = (void *) (index * 4096 * 8 + map_bit * 4096);
			pg_used(addr);
			return addr;
		}
	}
	panic("out of memory");
}

void pg_free(void *addr){
	if(addr > (void *) mem_max){
		return;
	}
	uint32_t map_index = (uint32_t) addr / 4096 / 8;
	uint32_t map_bit = (uint32_t) addr / 4096 % 8;

	page_map[map_index] &= ~(1 << map_bit);
	prev_index = map_index < prev_index ? map_index : prev_index;
}

void pg_used(void *addr){
	uint32_t map_index = (uint32_t) addr / 4096 / 8;
	uint32_t map_bit = (uint32_t) addr / 4096 % 8;

	page_map[map_index] |= 1 << map_bit;
}
