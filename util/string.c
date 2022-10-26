#include <stdint.h>
#include "string.h"

size_t strlen(const char *str)
{
	size_t len;
	for (len = 0; str[len]; ++len)
		;
	return len;
}

char *strcat(char *dest, const char *src)
{
	size_t dest_len = strlen(dest);
	size_t src_len = strlen(src);
	size_t i;
	for (i = 0; i < src_len; ++i)
	{
		dest[dest_len + i] = src[i];
	}
	dest[dest_len + i] = '\0';
	return dest;
}

int strcmp(const char *str1, const char *str2)
{
	size_t i;
	for (i = 0; str1[i] == str2[i]; ++i)
	{
		if (str1[i] == '\0')
		{
			return 0;
		}
	}
	return str1[i] - str2[i];
}

int strncmp(const char *str1, const char *str2, size_t num)
{
	while (num && *str1 && (*str1 == *str2))
	{
		++str1;
		++str2;
		--num;
	}
	if (num == 0)
	{
		return 0;
	}
	else
	{
		return *(unsigned char *)str1 - *(unsigned char *)str2;
	}
}

void *memcpy(void *dest, const void *src, size_t n)
{
	char *d = dest;
	const char *s = src;
	for (int i = 0; i <= (int)n; ++i)
	{
		d[i] = s[i];
	}
	return dest;
}

void *memmove(void *dest, const void *src, size_t n)
{
	char *d = dest;
	const char *s = src;
	if (src < dest)
	{
		for (int i = n; i >= 0; --i)
		{
			d[i] = s[i];
		}
	}
	else
	{
		for (int i = 0; i < (int)n; ++i)
		{
			d[i] = s[i];
		}
	}
	return dest;
}

volatile void *memmove_volatile(volatile void *dest, const volatile void *src, size_t n)
{
	volatile char *d = dest;
	const volatile char *s = src;
	if (src < dest)
	{
		for (int i = n; i >= 0; --i)
		{
			d[i] = s[i];
		}
	}
	else
	{
		for (int i = 0; i < (int)n; ++i)
		{
			d[i] = s[i];
		}
	}
	return dest;
}

void *memset(void *ptr, int x, size_t n)
{
	for (int i = 0; i < (int)n; ++i)
	{
		*((char *)ptr + i) = x;
	}
	return ptr;
}

volatile void *memset_volatile(volatile void *ptr, int x, size_t n)
{
	for (int i = 0; i < (int)n; ++i)
	{
		*((volatile char *)ptr + i) = x;
	}
	return ptr;
}

char *itoa(uint32_t val, char *buf, int base)
{
	char *rc;
	char *ptr;
	char *low;
	if (base < 2 || base > 36)
	{
		*buf = '\0';
		return buf;
	}
	rc = low = ptr = buf;
	do
	{
		*ptr++ = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[val % base];
		val /= base;
	} while (val);
	*ptr-- = '\0';
	while (low < ptr)
	{
		char tmp = *low;
		*low++ = *ptr;
		*ptr-- = tmp;
	}
	return rc;
}
