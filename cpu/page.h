#ifndef PAGE_H
#define PAGE_H

#include <stdint.h>
#include <stddef.h>

#define PG_PRESENT (1 << 0)
#define PG_WRITE (1 << 1)
#define PG_USER (1 << 2)

/* maps a single physical page to a virtual page
 * be aware that both are page aligned and thus the lower 12 bits (offset into
 * the page) should be the same or it should be taken into account that
 * addresses will need to be changed accordingly
 */
void pg_map(void *phys, void *virt, uint32_t flags);
void pg_unmap(void *addr);

void *pg_phys_addr(void *addr);

#endif /* PAGE_H */