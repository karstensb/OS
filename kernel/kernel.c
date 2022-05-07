#include "multiboot.h"
#include "cpu/idt.h"
#include "cpu/page.h"
#include "cpu/pic.h"
#include "cpu/tss.h"
#include "cpu/x86.h"
#include "drivers/screen.h"
#include "util/string.h"
#include "util/util.h"

void kmain(mbi_structure *mbi){
	UNUSED(mbi);
	tss_init();
	idt_init();
	pic_init();
	sti();
	enable_cursor(CURSOR_MIN, CURSOR_MAX);
	clear_screen();
	while(1){
		hlt();
	}
}

