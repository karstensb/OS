#ifndef PANIC_H
#define PANIC_H

#include <stdnoreturn.h>

noreturn void panic(const char *message);

#endif /* PANIC_H */