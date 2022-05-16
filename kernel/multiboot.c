#include "multiboot.h"
#include "cpu/page.h"
#include "util/util.h"

void *mbi_tag_get(mbi_structure *mbi, uint32_t type){
	mbi_tag *tag = (mbi_tag *)mbi->mbi_tags;
	while(tag->type != MBI_TAG_END){
		if(tag->type == type){
			return tag;
		}
		tag = (mbi_tag *) ((uint8_t *) tag + (tag->size+8-1) / 8 * 8);
	}
	return NULL;
}

void mbi_init(mbi_structure *mbi){
	pg_map((void *) mbi-KERNEL_BASE, mbi, PG_PRESENT);
	/* if the mbi crosses a page boundary, map the next page */
	if(mbi->total_size + pg_offset(mbi) > 4096){
		pg_map((void *) mbi-KERNEL_BASE + 4096, mbi + 4096, PG_WRITE);
	}
}