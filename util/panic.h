#pragma once

#include <stdnoreturn.h>

/* halt the cpu after printing an error message */
noreturn
void panic(const char *message);
