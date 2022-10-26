#pragma once

#include <stddef.h>

size_t strlen(const char *str);
char *strcat(char *dest, const char *src);
int strcmp(const char *str1, const char *str2);
int strncmp(const char *str1, const char *str2, size_t num);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
volatile void *memmove_volatile(volatile void *dest, const volatile void *src, size_t n);
void *memset(void *ptr, int x, size_t n);
volatile void *memset_volatile(volatile void *ptr, int x, size_t n);
/* only unsigned values are supported */
char *itoa(uint32_t val, char *buf, int base);
