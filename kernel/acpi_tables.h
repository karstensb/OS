#pragma once

#include <stdint.h>

struct rsdp
{
	char signature[8];
	uint8_t checksum;
	char oemid[6];
	uint8_t revision;
	uint32_t rsdt;
} __attribute__((packed));

struct sdt_header
{
	char signature[4];
	uint32_t length;
	uint8_t revision;
	uint8_t checksum;
	char oemid[6];
	char oem_table_id[8];
	uint32_t oem_revision;
	uint32_t creator_id;
	uint32_t creator_revision;
} __attribute__((packed));

struct rsdt
{
	struct sdt_header header;
	uint32_t sdt_pointers[];
} __attribute__((packed));

struct madt
{
	struct sdt_header header;
	uint32_t lapic;
	uint32_t dual_8259A_pic : 1;
	uint32_t : 31;
	uint16_t devices[];
} __attribute__((packed));
