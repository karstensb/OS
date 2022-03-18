#ifndef STRING_H
#define STRING_H

#include <stddef.h>

const size_t strlen(const char *str);
void *memcpy(void *dest, const void * src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *ptr, int x, size_t n);
char *itoa(int val, int base, char *buf);

#endif /* STRING_H */