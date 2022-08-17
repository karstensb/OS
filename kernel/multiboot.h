#pragma once

#include <stdint.h>

enum mbi_tags{
	MBI_TAG_END = 0,
	MBI_TAG_BOOT_DEV = 5,
	MBI_TAG_MMAP = 6,
	MBI_TAG_RSDP_OLD = 14
};

struct mbi_tag{
	uint32_t type;
	uint32_t size;
}__attribute__((packed));

struct mbi_structure{
	uint32_t total_size;
	uint32_t reserved;
	struct mbi_tag mbi_tags[];
}__attribute__((packed));


struct mbi_tag_bootdev{
	uint32_t type;
	uint32_t size;
	uint32_t biosdev;
	uint32_t partition;
	uint32_t sub_partition;
}__attribute__((packed));

struct mbi_mmap_entry{
	uint64_t base_addr;
	uint64_t length;
	uint32_t type;
	uint32_t reserved;
}__attribute__((packed));

struct mbi_tag_mmap{
	uint32_t type;
	uint32_t size;
	uint32_t entry_size;
	uint32_t entry_version;
	struct mbi_mmap_entry entries[];
}__attribute__((packed));

extern struct mbi_structure *mbi;

void *mbi_get_tag(uint32_t type);
