#include "multiboot.h"
#include "cpu/tss.h"
#include "cpu/idt.h"
#include "cpu/page.h"
#include "cpu/pic.h"
#include "cpu/x86.h"
#include "drivers/screen.h"
#include "util/util.h"

void kmain(mbi_structure *mbi){
	idt_init();
	mbi_init(mbi);
	pg_init(mbi);
	pic_init();
	tss_init();
	sti();
	enable_cursor(CURSOR_MIN, CURSOR_MAX);
	clear_screen();
	for(;;);
}
