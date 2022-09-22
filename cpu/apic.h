#pragma once

#include <stdint.h>

#define APIC_LVT_MASKED (1 << 16)

void apic_eoi(void);
void apic_init(void);
