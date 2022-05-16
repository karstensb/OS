//TODO: pag_dir[5] doesnt necessarily point to page_tables[5]



#include "page.h"
#include "x86.h"
#include "util/panic.h"

extern uint32_t _kernel_start;
extern uint32_t _kernel_end;

uint32_t page_dir[1024] __attribute__((aligned(4096)));
uint32_t page_tables[1024][1024] __attribute__((aligned(4096)));

/* bitmap of physical pages */
static uint8_t *pg_map_phys;
/* ram size in bytes */
static uint32_t mem_max;

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
		if(addr > mem_max){
			mem_max = addr;
		}
	}

	pg_map_phys = (uint8_t *) ((uint32_t) mbi + mbi->total_size);
	/* get the size of the physical page map (each bit maps to a physical page) */
	void *pg_map_end = pg_map_phys + mem_max/4096/8;
	/* map all pages containing pg_map_phys (calculated by first free address after kernel + pg_phys_map_size) to the kernel*/
	for(void *addr = pg_map_phys; addr <= pg_map_end+4096; addr += 4096){
		pg_map(addr-KERNEL_BASE, addr, PG_PRESENT);
	}

	/* mark pg_map_phys as used */
	for(void *addr = pg_map_phys; addr <= pg_map_end; addr += 4096){
		pg_used(addr-KERNEL_BASE);
	}

	/* mark the first mib (256 pages = 32 * 8 bit) as used */
	for(int i = 0; i < 32; ++i){
		pg_map_phys[i] = 0xFF;
	}

	/* mark reserved pages as used */
	for(int i = 0; i < mbi_mmap_count; ++i){
		if (mmap_tag->entries[i].type != 1){
			for(void *addr = (void *) (uint32_t) mmap_tag->entries[i].base_addr;
				addr < (void *) (uint32_t) mmap_tag->entries[i].base_addr + mmap_tag->entries[i].length;
				addr += 4096){

				pg_used(addr);
			}
		}
	}

	/* mark kernel pages as used */
	for(void *addr = (void *) &_kernel_start; addr <= (void *) &_kernel_end; addr += 4096){
		pg_used(addr);
	}

	/* mark mbi as used */
	pg_used((void *) mbi-KERNEL_BASE);
	/* if the mbi crosses a page boundary, mark the next page as used */
	if(mbi->total_size + pg_offset(mbi) > 4096){
		pg_used((void *) mbi-KERNEL_BASE + 4096);
	}
}

/* void *pg_alloc(void){
} */

void pg_free(void *addr){
	addr = (void *) ((int) addr & 0xFFFFF000);
	uint32_t map_index = (uint32_t) addr / 4096 / 8;
	uint32_t map_bit = (uint32_t) addr / 4096 % 8;

	pg_map_phys[map_index] &= ~(1 << map_bit);
}

void pg_used(void *addr){
	addr = (void *) ((int) addr & 0xFFFFF000);
	uint32_t map_index = (uint32_t) addr / 4096 / 8;
	uint32_t map_bit = (uint32_t) addr / 4096 % 8;

	pg_map_phys[map_index] |= 1 << map_bit;
}