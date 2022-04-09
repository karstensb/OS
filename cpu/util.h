#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

#define CLI asm volatile ("cli");
#define STI asm volatile ("sti");

#endif /* UTIL_H */