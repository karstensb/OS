#ifndef GDT_H
#define GDT_H

#include <stdint.h>

extern uint8_t gdt_start;
extern uint8_t gdt_kernel_cs;
extern uint8_t gdt_kernel_ds;
extern uint8_t gdt_user_cs;
extern uint8_t gdt_user_ds;
extern uint8_t gdt_tss;
extern uint8_t gdt_end;

#define KERNEL_CS (&gdt_kernel_cs - &gdt_start)
#define KERNEL_DS (&gdt_kernel_ds - &gdt_start)
#define USER_CS (&gdt_user_cs - &gdt_start)
#define USER_DS (&gdt_user_ds - &gdt_start)
#define GDT_TSS (&gdt_tss - &gdt_start)

#endif /* GDT_H */