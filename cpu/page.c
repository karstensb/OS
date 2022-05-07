#include "page.h"
#include "x86.h"

uint32_t page_dir[1024] __attribute__((aligned(4096)));
uint32_t page_tables[1024][1024] __attribute__((aligned(4096)));

static inline uint32_t page_dir_index(void *addr){
	return (((uint32_t) addr) >> 22) & 0x3FF;
}

static inline uint32_t page_tb_index(void *addr){
	return (((uint32_t) addr) >> 12) & 0x3FF;
}

static inline uint32_t page_offset(void *addr){
	return ((uint32_t) addr) & 0xFFF;
}

void *pg_phys_addr(void *addr){
	uint32_t dir_index = page_dir_index(addr);
	uint32_t tb_index = page_tb_index(addr);
	uint32_t offset = page_offset(addr);

	return (void *) page_tables[dir_index][tb_index] + offset;
}

void pg_map(void *phys, void *virt, uint32_t flags){
	uint32_t dir_index = page_dir_index(virt);
	uint32_t tb_index = page_tb_index(virt);

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
	uint32_t dir_index = page_dir_index(addr);
	uint32_t tb_index = page_tb_index(addr);

	/* see above */
	page_tables[dir_index][tb_index] = 0;
}