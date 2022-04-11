#ifndef PIC_H
#define PIC_H

#include <stdint.h>

#define PIC_TIMER (0)
#define PIC_KEYBOARD (1)
#define PIC_SLAVE (2)
#define PIC_COM2 (3)
#define PIC_COM1 (4)
#define PIC_LPT2 (5)
#define PIC_FLOPPY (6)
#define PIC_LPT1 (7)
#define PIC_RTC (8)
#define PIC_CGA (9)
#define PIC_RESERVED_1 (10)
#define PIC_RESERVED_2 (11)
#define PIC_RESERVED_3 (12)
#define PIC_FPU (13)
#define PIC_HDD (14)
#define PIC_RESERVED_4 (15)

void init_pic(void);
void pic_eoi(uint8_t irq);
uint16_t pic_get_isr(void);
void irq_enable(uint8_t irq);
void irq_disable(uint8_t irq);

#endif /* PIC_H */