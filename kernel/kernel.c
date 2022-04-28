#include "cpu/idt.h"
#include "cpu/pic.h"
#include "cpu/tss.h"
#include "cpu/x86.h"
#include "drivers/screen.h"
#include "drivers/keyboard.h"
#include "util/string.h"
#include "util/util.h"

void kmain(void *multiboot_structure){
	UNUSED(multiboot_structure);
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