#ifndef STRING_H
#define STRING_H

size_t strlen(const char *str);
char *strcat(char *dest, const char *src);
void *memcpy(void *dest, const void * src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *ptr, int x, size_t n);
char *itoa(int val, char *buf, int base);

/* convert an unsigned value to a hex string */
char *to_hex(unsigned int val, char *buf);

#endif /* STRING_H */