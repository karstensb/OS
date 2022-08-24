#include "panic.h"
#include "cpu/x86.h"
#include "drivers/screen.h"

noreturn
void panic(const char *message)
{
	cli();
	set_terminal_color(VGA_COLOR_RED, VGA_COLOR_BLACK);
	kprintc('\n');
	kprint(message);
	kprint("\n\nHalting the CPU...");
	disable_cursor();
	for (;;)
	{
		hlt();
	}
}
