#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
static inline
void cli(void){
	asm("cli");
}

static inline
void sti(void){
	asm("sti");
}

static inline
void hlt(void){
	asm("hlt");
}

static inline
uint8_t inb(uint16_t port){
	uint8_t result;
	asm volatile("in al, dx" : "=a" (result) : "d" (port));
	return result;
}


static inline
void outb(uint16_t port, uint8_t data){
	asm("out dx, al" : : "a" (data), "d" (port));
}

#endif /* UTIL_H */