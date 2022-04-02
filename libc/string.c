#include "string.h"
#include <stdint.h>

const size_t strlen(const char *str){
	size_t len;
	for (len = 0; str[len]; ++len);
	return len;
}

void *memcpy(void *dest, const void * src, size_t n){
	char *d = dest;
	const char *s = src;
	for (int i = 0; i <= n; ++i){
		d[i] = s[i];
	}
	return dest;
}

void *memmove(void *dest, const void *src, size_t n){
	char *d = dest;
	const char *s = src;
	if (src < dest){
		for (int i = n; i >= 0; --i){
			d[i] = s[i];
		}
	}
	else{
		for (int i = 0; i < n; ++i){
			d[i] = s[i];
		}
	}
	return dest;
}

void *memset(void *ptr, int x, size_t n){
	for (int i = 0; i < n; ++i){
		*((uint8_t *) ptr + i) = x;
	}
}

char *itoa(int val, char *buf, int base){
	char *rc;
	char *ptr;
	char *low;
	if ( base < 2 || base > 36 ){
		*buf = '\0';
		return buf;
	}
	rc = ptr = buf;
	if (val < 0 && base == 10 ){
		*ptr++ = '-';
	}
	low = ptr;
	do{
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + val % base];
		val /= base;
	}while (val);
	*ptr-- = '\0';
	while ( low < ptr ){
		char tmp = *low;
		*low++ = *ptr;
		*ptr-- = tmp;
	}
	return rc;
}