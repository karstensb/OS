#include "drivers/screen.h"
#include "drivers/keyboard.h"
#include "util/string.h"

void kmain(/* void *multiboot_structure */){
	init_tss();
	init_idt();
	init_pic();
	sti();
	enable_cursor(CURSOR_MIN, CURSOR_MAX);
	clear_screen();
	while(1){
		hlt();
	}
}