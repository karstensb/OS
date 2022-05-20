#ifndef PANIC_H
#define PANIC_H

#include <stdnoreturn.h>

/* halt the cpu after printing an error message */
noreturn void panic(const char *message);

#endif /* PANIC_H */