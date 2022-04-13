#include "../drivers/screen.h"
#include "../libc/string.h"
#include "../cpu/idt.h"
#include "../cpu/pic.h"
#include "../cpu/tss.h"

void kernel_main(void){
	init_tss();
	init_idt();
	init_pic();
	enable_cursor(CURSOR_MIN, CURSOR_MAX);
	clear_screen();
}