#include "../drivers/screen.h"
#include "../util/string.h"
#include "../cpu/idt.h"
#include "../cpu/pic.h"
#include "../cpu/tss.h"
#include "../cpu/util.h"

void kernel_main(/* void *multiboot_structure */){
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