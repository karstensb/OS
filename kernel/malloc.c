#include <stdint.h>
#include "malloc.h"
#include "cpu/page.h"
#include "util/string.h"

struct heap_header
{
	size_t size;
	struct heap_header *next;
	char data[];
};

/* start of the heap */
static void *heap;
static void *heap_end;
/* pointer to the first allocated block */
static struct heap_header *heap_head;

void malloc_init(void *heap_start, size_t size)
{
	/* initialize a first block of size 0 on the heap */
	heap = heap_start;
	heap_end = heap_start + size;
	heap_head = (struct heap_header *)heap_start;
	heap_head->size = 0;
	heap_head->next = NULL;
	// TODO: use brk/sbrk equivalent to dynamically allocate the heap
	/* map the heap */
	for (void *ptr = heap_start; ptr <= heap_start + size; ptr += 4096)
	{
		pg_map(pg_alloc(), ptr, PG_PRESENT);
	}
	memset(heap, 0, size);
}

void *malloc(size_t size)
{
	struct heap_header *current = heap_head;
	/* first use of malloc, nothing has been allocated yet */
	if (current->size == 0)
	{
		current->size = size + sizeof(struct heap_header);
		current->next = NULL;
		return (void *)current->data;
	}
	/* is the block between heap and the first allocated block big enough? */
	if ((size_t)((void *)heap_head - heap) >= size + sizeof(struct heap_header))
	{
		current = (struct heap_header *)heap;
		current->size = size;
		current->next = heap_head;
		heap_head = current;
		return (void *)current->data;
	}
	do
	{
		/* have we reached the end of the heap? */
		if (current->next == NULL)
		{
			/* the heap is not big enough */
			if ((void *)current->next + size > heap_end)
			{
				return NULL;
			}
			current->next = (struct heap_header *)((void *)current + current->size);
			current->next->next = NULL;
			current->next->size = size + sizeof(struct heap_header);
			return (void *)current->next->data;
		}
		current = current->next;
	} while (current->next == NULL || ((ptrdiff_t)current->next - ((ptrdiff_t)current + current->size) <= size + sizeof(struct heap_header)));

	/* there is enough space between current and current->next */
	struct heap_header *temp = current->next;
	current->next = (struct heap_header *)((void *)current + current->size);
	current->next->size = size + sizeof(struct heap_header);
	current->next->next = temp;
	return (void *)current->data;
}

void free(void *ptr)
{
	if (ptr == NULL)
	{
		return;
	}
	/* the pointer points to the data of the block which is preceded by a heap_header */
	ptr -= sizeof(struct heap_header);
	struct heap_header *current = heap_head;
	
	/* should we free the first block? */
	if (heap_head == ptr)
	{
		heap_head = heap_head->next;
		return;
	}
	while (current->next != NULL)
	{
		if ((void *)current->next == ptr)
		{
			current->next = current->next->next;
			return;
		}
		current = current->next;
	}
}

void *calloc(size_t nmemb, size_t size)
{
	void *ptr = malloc(nmemb * size);
	if (ptr)
	{
		memset(ptr, 0, nmemb * size);
	}
	return ptr;
}

void *realloc(void *ptr, size_t size)
{
	void *new_ptr = malloc(size);
	if (new_ptr)
	{
		memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return new_ptr;
}
