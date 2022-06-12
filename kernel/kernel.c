#include "multiboot.h"
#include "cpu/apic.h"
#include "cpu/tss.h"
#include "cpu/isr.h"
#include "cpu/page.h"
#include "cpu/x86.h"
#include "drivers/screen.h"
#include "util/string.h"

mbi_structure *mbi;

void kmain(mbi_structure *mbi_ptr){
	mbi = mbi_ptr;
	isr_init();
	pg_init();
	apic_init();
	tss_init();
	sti();
	enable_cursor(CURSOR_MIN, CURSOR_MAX);
	clear_screen();
	for(;;);
}