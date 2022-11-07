#pragma once

#include <stdint.h>

#define APIC_LVT_MASKED (1 << 16)

__attribute__((no_caller_saved_registers))
void apic_init(void);
