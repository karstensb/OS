#pragma once

#include <stddef.h>

void malloc_init(void *heap_start, size_t heap_size);
void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
