#pragma once

#include <stddef.h>

/* alloc a block of pages in virtual memory of at least 'size' bytes */
void *alloc_pages(size_t size);
void free_pages(void *addr);