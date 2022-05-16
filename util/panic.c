#include "panic.h"
#include "cpu/x86.h"
#include "drivers/screen.h"

noreturn void panic(const char *message){
	cli();
	set_terminal_color(VGA_COLOR_RED, VGA_COLOR_WHITE);
	kprint("\n\n");
	kprint(message);
halt:
	hlt();
	goto halt;
}