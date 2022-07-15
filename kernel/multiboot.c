#include <stddef.h>
#include "multiboot.h"
#include "cpu/page.h"

mbi_structure *mbi;

void *mbi_tag_get(uint32_t type){
	mbi_tag *tag = (mbi_tag *)mbi->mbi_tags;
	while(tag->type != MBI_TAG_END){
		if(tag->type == type){
			return tag;
		}
		tag = (mbi_tag *) ((uint8_t *) tag + (tag->size+8-1) / 8 * 8);
	}
	return NULL;
}
