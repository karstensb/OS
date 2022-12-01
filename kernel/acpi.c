#include <stdbool.h>
#include <stdint.h>
#include "acpi.h"
#include "malloc.h"
#include "multiboot.h"
#include "v_malloc.h"
#include "cpu/page.h"
#include "util/string.h"
#include "util/panic.h"

static struct rsdp rsdp;
static struct rsdt *rsdt;
static int num_sdt;

static bool calc_checksum(struct sdt_header *sdt)
{
	uint8_t sum = 0; /* will overflow, however only lower 8 bits are important */
	for (unsigned i = 0; i < sdt->length; ++i)
	{
		sum += ((char *)sdt)[i];
	}

	return sum == 0;
}

/* TODO: breaks page table mappings */
static void init(void)
{
	/* discard mbi tag information (8 bytes) and get the actual rsdp */
	struct rsdp *rsdp_phys = (struct rsdp *)(mbi_get_tag(MBI_TAG_RSDP_OLD) + 8);

	/* map the table into memory, considering that it isn't page aligned */
	void *temp = alloc_pages(sizeof(struct rsdp)) + (size_t)rsdp_phys % 4096;
	pg_map((void *)rsdp_phys, temp, PG_PRESENT);
	/* copy the rsdp to kernel memory */
	memcpy(&rsdp, rsdp_phys, sizeof(struct rsdp));

	free_pages(temp - (size_t)rsdp_phys % 4096);

	struct rsdt *rsdt_phys = (struct rsdt *)rsdp.rsdt;
	/* map the table into memory, considering that it isn't page aligned */
	temp = alloc_pages(sizeof(struct rsdt)) + (size_t)rsdt_phys % 4096;
	pg_map((void *)rsdt_phys, temp, PG_PRESENT); /* TODO: issue is here, alloc_pages returns a used address  */
	/* allocate memory for the rsdt and copy it there */
	rsdt = malloc(((struct rsdt *)temp)->header.length);
	memcpy(rsdt, temp, ((struct rsdt *)temp)->header.length);

	free_pages(temp - (size_t)rsdt_phys % 4096);

	if (!calc_checksum((struct sdt_header *)rsdt))
	{
		panic("Error while parsing acpi tables: rsdt invalide checksum");
	}

	num_sdt = (rsdt->header.length - sizeof(struct sdt_header)) / 4;
}

void *acpi_get_table(const char signature[static 4])
{
	static bool initialized = false;
	if (!initialized)
	{
		init();
		initialized = true;
	}

	for (int i = 0; i < num_sdt; ++i)
	{
		/* temporarily map the current table into memory */
		struct sdt_header *sdt_phys = (struct sdt_header *)rsdt->sdt_pointers[i];
		void *temp = alloc_pages(sizeof(struct sdt_header)) + (size_t)sdt_phys;
		pg_map((void *)sdt_phys, temp, PG_PRESENT);

		struct sdt_header *sdt_old = temp;
		if (!strncmp(sdt_old->signature, signature, 4) && calc_checksum(sdt_old))
		{
			/* copy the table to the kernel heap */
			struct sdt_header *sdt = malloc(sdt_old->length);
			memcpy(sdt, sdt_old, sdt_old->length);
			/* free the temporarily allocated pages */
			free_pages(temp - (size_t)sdt_old);
			return sdt;
		}
		/* free the temporarily allocated pages */
		free_pages(temp - (size_t)sdt_old);
	}
	return NULL;
}
