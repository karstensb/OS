#include "v_malloc.h"
#include "malloc.h"
#include "cpu/page.h"

#define V_HEAP_START 0xE8000000

struct heap_header
{
	void *addr;
	size_t size;
	struct heap_header *next;
};

/* pointer to the first allocated block of pages */
static struct heap_header *heap_head = NULL;

void *alloc_pages(size_t size)
{
	size += (size % 4096 != 0) ? (4096 - size % 4096) : 0; /* make size a multiple of 4096 for ease of use */
	struct heap_header *current = heap_head;

	/* first call to alloc_pages, initialize */
	if (current == NULL)
	{
		current = malloc(sizeof(struct heap_header));
		current->addr = (void *)V_HEAP_START;
		current->size = size;
		current->next = NULL;
		heap_head = current;
	}
	/* is there enough space at the start of the heap? */
	else if ((size_t)heap_head->addr - V_HEAP_START >= size)
	{
		heap_head = malloc(sizeof(struct heap_header));
		heap_head->addr = (void *)V_HEAP_START;
		heap_head->size = size;
		heap_head->next = current;
		current = heap_head;
	}
	else
	{
		while (current->next != NULL)
		{
			/* is there enough space between the current and the next block */
			if ((size_t)current->next->addr - ((size_t)current->addr + current->size)
			    > size)
			{
				break;
			}
			current = current->next;
		}

		/* the end of the virtual heap has been reached */
		if (current->next == NULL)
		{
			/* there is no more space in virtual memory*/
			if ((size_t)current->addr + current->size + size > 0xFFFFFFFF)
			{
				return NULL;
			}
			current->next = malloc(sizeof(struct heap_header));
			current->next->addr = current->addr + current->size;
			current->next->size = size;
			current->next->next = NULL;
			current = current->next;
		}
		else /* found a gap that is large enough and didn't reach the end */
		{
			struct heap_header *temp = current->next;
			current->next = malloc(sizeof(struct heap_header));
			current->next->addr = current->addr + current->size;
			current->next->size = size;
			current->next->next = temp;
			current = current->next;
		}
	}
	return current->addr;
}

void free_pages(void *addr)
{
	if (addr == NULL)
	{
		return;
	}

	struct heap_header *current = heap_head;
	struct heap_header *temp;

	/* should we free the first block? */
	if (heap_head == addr)
	{
		temp = heap_head;
		heap_head = heap_head->next;
		free(heap_head);
		return;
	}
	while (current->next != NULL)
	{
		if ((void *)current->next->addr == addr)
		{
			temp = current;
			current->next = current->next->next;
			free(temp->next);
			return;
		}
		current = current->next;
	}
}