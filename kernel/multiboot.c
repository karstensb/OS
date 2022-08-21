#include <stddef.h>
#include "multiboot.h"

struct mbi_structure *mbi; //filled by boot.s

void *mbi_get_tag(uint32_t type){
	struct mbi_tag *tag = (struct mbi_tag *)mbi->mbi_tags;
	while(tag->type != MBI_TAG_END){
		if(tag->type == type){
			return tag;
		}
		tag = (struct mbi_tag *) ((uint8_t *) tag + (tag->size+8-1) / 8 * 8);
	}
	return NULL;
}
