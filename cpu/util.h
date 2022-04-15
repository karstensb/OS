#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include "gdt.h"
#include "idt.h"

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

static inline
void lgdt(gdt_descriptor_t *gdt_descriptor){
	asm("lgdt [%0]" : : "r" (gdt_descriptor));
}

static inline
void lidt(idt_descriptor_t *idt_descriptor){
	asm("lidt [%0]" : : "r" (idt_descriptor));
}

static inline
void ltr(uint16_t selector){
	asm("ltr %0" : : "r" (selector));
}

#endif /* UTIL_H */