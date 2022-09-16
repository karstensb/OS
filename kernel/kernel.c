#include "multiboot.h"
#include "malloc.h"
#include "cpu/apic.h"
#include "cpu/tss.h"
#include "cpu/isr.h"
#include "cpu/page.h"
#include "cpu/x86.h"
#include "drivers/screen.h"
#include "util/string.h"

#define HEAP_SIZE (16384)

void kmain(void)
{
	isr_init();
	pg_init();
	malloc_init((void *)mbi + mbi->total_size, HEAP_SIZE);
	apic_init();
	tss_init();
	sti();
	enable_cursor(CURSOR_MIN, CURSOR_MAX);
	clear_screen(0);
	for (;;)
		;
}
