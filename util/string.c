#include <stdint.h>
#include <stddef.h>
#include "string.h"

size_t strlen(const char *str){
	size_t len;
	for (len = 0; str[len]; ++len);
	return len;
}

char *strcat(char *dest, const char *src){
	size_t dest_len = strlen(dest);
	size_t src_len = strlen(src);
	size_t i;
	for (i = 0; i < src_len; ++i){
		dest[dest_len + i] = src[i];
	}
	dest[dest_len + i] = '\0';
	return dest;
}

void *memcpy(void *dest, const void * src, size_t n){
	char *d = dest;
	const char *s = src;
	for (int i = 0; i <= (int) n; ++i){
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
		for (int i = 0; i < (int) n; ++i){
			d[i] = s[i];
		}
	}
	return dest;
}

void *memset(void *ptr, int x, size_t n){
	for (int i = 0; i < (int) n; ++i){
		*((uint8_t *) ptr + i) = x;
	}
	return ptr;
}

char *to_hex(unsigned int val, char *buf){
	char *ptr = buf;
	char *low = ptr;
	do{
		*ptr++ = "0123456789ABCDEF"[val & 0xF];
		val >>= 4;
	}while(val);
	*ptr-- = '\0';
	while(low < ptr){
		char tmp = *low;
		*low++ = *ptr;
		*ptr-- = tmp;
	}
	return buf;
}

char *itoa(int val, char *buf, int base){
	char *rc;
	char *ptr;
	char *low;
	if(base < 2 || base > 36){
		*buf = '\0';
		return buf;
	}
	rc = ptr = buf;
	if(val < 0 && base == 10 ){
		*ptr++ = '-';
	}
	low = ptr;
	do{
		*ptr++ = "ZYXWVUTSRQPONMLKJIHGFEDCBA9876543210123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[35 + val % base];
		val /= base;
	}while(val);
	*ptr-- = '\0';
	while(low < ptr){
		char tmp = *low;
		*low++ = *ptr;
		*ptr-- = tmp;
	}
	return rc;
}