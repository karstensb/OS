#ifndef PIC_H
#define PIC_H

#include <stdint.h>

#define PIC1_CMD (0x20)
#define PIC1_DATA (0x21)
#define PIC2_CMD (0xA0)
#define PIC2_DATA (0xA1)

#define ICW1_ICW4 (0x01)
#define ICW1_INIT (0x10)

#define ICW4_8086 (0x01)

#define PIC_EOI (0x20)

#define PIC_READ_ISR (0x0b)

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