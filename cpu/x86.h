#ifndef X86_H
#define X86_H

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
uint16_t inw(uint16_t port){
	uint16_t result;
	asm volatile("in ax, dx" : "=a" (result) : "d" (port));
	return result;
}

static inline
uint32_t inl(uint16_t port){
	uint32_t result;
	asm volatile("in eax, dx" : "=a" (result) : "d" (port));
	return result;
}

static inline
void outb(uint16_t port, uint8_t data){
	asm("out dx, al" : : "a" (data), "d" (port));
}

static inline
void outw(uint16_t port, uint16_t data){
	asm("out dx, ax" : : "a" (data), "d" (port));
}

static inline
void outl(uint16_t port, uint32_t data){
	asm("out dx, eax" : : "a" (data), "d" (port));
}

static inline
void lgdt(uint16_t size, uint32_t offset){
	gdt_descriptor gdt_descr;
	gdt_descr.size = size;
	gdt_descr.offset = offset;
	asm("lgdt [%0]" : : "r" (&gdt_descr));
}

static inline
void lidt(uint16_t size, uint32_t offset){
	idt_descriptor idt_descr;
	idt_descr.size = size;
	idt_descr.offset = offset;
	asm("lidt [%0]" : : "r" (&idt_descr));
}

static inline
void ltr(uint16_t selector){
	asm("ltr %0" : : "r" (selector));
}

static inline
void wrmsr(uint32_t msr, uint32_t low, uint32_t high){
	asm("wrmsr" : : "c" (msr), "a" (low), "d" (high));
}

static inline
void rdmsr(uint32_t msr, uint32_t low, uint32_t high){
	asm("rdmsr" : "=a" (low), "=d" (high) : "c" (msr));
}

static inline
uint32_t rcr2(){
	uint32_t cr2;
	asm("mov %0, cr2" : "=r" (cr2));
	return cr2;
}

static inline
void invlpg(void *addr){
	asm("invlpg [%0]" : : "r" ((uint32_t) addr));
}

#endif /* X86_H */