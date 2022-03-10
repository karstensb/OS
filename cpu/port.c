#include "port.h"

uint8_t inb(uint16_t port){
	uint8_t result;
	asm("in al, dx" : "=a" (result) : "d" (port));
	return result;
}

void outb(uint16_t port, uint8_t data){
	asm("out dx, al" : : "a" (data), "d" (port));
}