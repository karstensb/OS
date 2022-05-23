//TODO: pag_dir[5] doesnt necessarily point to page_tables[5]

#include <limits.h>
#include "page.h"
#include "x86.h"
#include "util/string.h"
#include "util/panic.h"

uint32_t page_dir[1024] __attribute__((aligned(4096)));
uint32_t page_tables[1024][1024] __attribute__((aligned(4096)));

/* bitmap of physical pages */
static int8_t *pg_map_phys;
/* ram size in bytes */
static uint32_t mem_max;
/* pointer to the first free physical page */
static uint32_t prev_index = 0;

void *pg_phys_addr(void *addr){
	uint32_t dir_index = pg_dir_index(addr);
	uint32_t tb_index = pg_tb_index(addr);
	uint32_t offset = pg_offset(addr);

	return (void *) ((page_tables[dir_index][tb_index] & 0xFFFFF000) + offset);
}

void pg_map(void *phys, void *virt, uint32_t flags){
	uint32_t dir_index = pg_dir_index(virt);
	uint32_t tb_index = pg_tb_index(virt);

	flags |= PG_PRESENT;
	if(!page_dir[dir_index]){
		/* see below */
		page_dir[dir_index] = (uint32_t) &page_tables[dir_index] | flags;
	}else{
		page_dir[dir_index] |= flags;
	}
	/* each page_dir entry points to the page table at the same offset
	 * i.e. page_dir[5] points to page_tables[5] 
	 * this is to be able to use [page_tables[dir_index]
	 * otherwsie, we would have to use [page_dir[dir_index]]
	 * and mapping/allocating would be much harder
	 */
	page_tables[dir_index][tb_index] = ((uint32_t) phys & 0xFFFFF000) | flags;
	invlpg(virt);
}

void pg_unmap(void *addr){
	uint32_t dir_index = pg_dir_index(addr);
	uint32_t tb_index = pg_tb_index(addr);

	/* see above */
	page_tables[dir_index][tb_index] = 0;
}



void pg_init(mbi_structure *mbi){
	struct mbi_tag_mmap *mmap_tag = mbi_tag_get(mbi, MBI_TAG_MMAP);
	/* mmap_tag->size includes the tag header which has to be subtracted */
	int mbi_mmap_count = (mmap_tag->size - sizeof(struct mbi_tag_mmap)) / sizeof(struct mbi_mmap_entry);

	/* find the maximum physical address */
	for(int i = 0; i < mbi_mmap_count; ++i){
		uint32_t addr = (uint32_t) mmap_tag->entries[i].base_addr+mmap_tag->entries[i].length;
		/* only update mem_max if the area is available, as all 4Gs might be
		   listed even though less is available */
		if(addr > mem_max && mmap_tag->entries[i].type == 1){
			mem_max = addr;
		}
	}

	pg_map_phys = (int8_t *) ((uint32_t) mbi + mbi->total_size);
	/* end of the physical page map (each bit maps to a physical page) */
	void *pg_map_end = pg_map_phys + mem_max/4096/8;
	/* map all pages containing pg_map_phys (calculated by first free address after kernel + pg_phys_map_size) to the kernel*/
	for(void *addr = pg_map_phys; addr <= pg_map_end+4096; addr += 4096){
		pg_map(addr-KERNEL_BASE, addr, PG_PRESENT);
	}

	memset(pg_map_phys, 0, mem_max/4096/8);

	/* The whole area from 0 to pg_map_end is marked as used as the first 1M is
	 * almost unusable, the kernel comes at 1M and should be closely followed by
	 * the mbi, which in turn is directly followed by pg_map_phys, ending at
	 * pg_map_end*/
	memset(pg_map_phys, UINT_MAX, ((int) pg_map_end - KERNEL_BASE)/4096/8 + 1);

	/* mark reserved pages as used */
	for(int i = 0; i < mbi_mmap_count; ++i){
		if (mmap_tag->entries[i].type != 1 && mmap_tag->entries[i].base_addr < mem_max){
			for(void *addr = (void *) (uint32_t) mmap_tag->entries[i].base_addr;
				addr < (void *) (uint32_t) mmap_tag->entries[i].base_addr + mmap_tag->entries[i].length;
				addr += 4096){

				pg_used(addr);
			}
		}
	}
}

void *pg_alloc(void){
	for(uint32_t index = prev_index; index < mem_max/4096/8; ++index){
		/* if at least one bit isn't set */
		if(~pg_map_phys[index] & 0xFF){
			int map_bit = 0;
			while(!((~pg_map_phys[index] >> map_bit) & 0x1)){
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
	uint32_t map_index = (uint32_t) addr / 4096 / 8;
	uint32_t map_bit = (uint32_t) addr / 4096 % 8;

	pg_map_phys[map_index] &= ~(1 << map_bit);
	prev_index = map_index < prev_index ? map_index : prev_index;
}

void pg_used(void *addr){
	uint32_t map_index = (uint32_t) addr / 4096 / 8;
	uint32_t map_bit = (uint32_t) addr / 4096 % 8;

	pg_map_phys[map_index] |= 1 << map_bit;
}