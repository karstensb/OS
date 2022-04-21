#ifndef STRING_H
#define STRING_H

size_t strlen(const char *str);
void *memcpy(void *dest, const void * src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *ptr, int x, size_t n);
char *itoa(int val, char *buf, int base);

#endif /* STRING_H */