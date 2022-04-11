#include "../drivers/screen.h"
#include "../libc/string.h"
#include "../cpu/isr.h"
#include "../cpu/pic.h"

void kernel_main(void){
	isr_install();
	enable_cursor(CURSOR_MIN, CURSOR_MAX);
	clear_screen();
	init_pic();
}