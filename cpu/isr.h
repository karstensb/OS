#ifndef ISR_H
#define ISR_H

#include <stdint.h>

typedef struct registers{
	uint16_t ds;
	uint16_t _padding0;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t int_no;
	/* sometimes pushed by hardware, otherwise manually pushed */
	uint32_t err_code;
	/* pushed by hardware */
	uint32_t eip;
	uint16_t cs;
	uint16_t _padding1;
	uint32_t eflags;
	/* only on cpl change*/
	uint32_t user_esp;
	uint16_t user_ss;
	uint16_t _padding2;
}__attribute__((packed)) registers_t;

void register_irq_handler(int irq, void (*handler)(registers_t *regs));

#endif /* ISR_H */