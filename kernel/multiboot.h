#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>

#define MBI_TAG_END (0)
#define MBI_TAG_BOOT_DEV (5)
#define MBI_TAG_MMAP (6)

typedef struct mbi_tag{
	uint32_t type;
	uint32_t size;
}mbi_tag;

typedef struct mbi_structure{
	uint32_t total_size;
	uint32_t reserved;
	mbi_tag mbi_tags[0];
}mbi_structure;


struct mbi_tag_bootdev{
	uint32_t type;
	uint32_t size;
	uint32_t biosdev;
	uint32_t partition;
	uint32_t sub_partition;
};

struct mbi_tag_mmap_entry{
	uint64_t base_addr;
	uint64_t length;
	uint32_t type;
	uint32_t reserved;
};

struct mbi_tag_mmap{
	uint32_t type;
	uint32_t size;
	uint32_t entry_size;
	uint32_t entry_version;
	struct mbi_tag_mmap_entry entries[0];
};

void *mbi_tag_get(mbi_structure *mbi, uint32_t type);

#endif /* MULTIBOOT_H */