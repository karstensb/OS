#ifndef PIC_H
#define PIC_H

#include <stdint.h>

enum irqs{
	PIC_TIMER = 0,
	PIC_KEYBOARD = 1,
	PIC_SLAVE = 2,
	PIC_COM2 = 3,
	PIC_COM1 = 4,
	PIC_LPT2 = 5,
	PIC_FLOPPY = 6,
	PIC_LPT1 = 7,
	PIC_RTC = 8,
	PIC_CGA = 9,
	PIC_FPU  = 13,
	PIC_HDD  = 14,
};

void pic_init(void);
void pic_disable(void);
void pic_eoi(uint8_t irq);
uint16_t pic_get_isr(void);
void irq_enable(uint8_t irq);
void irq_disable(uint8_t irq);

#endif /* PIC_H */