#include "../drivers/screen.h"
#include "../cpu/port.h"
#include "../libc/string.h"
#include "../cpu/isr.h"
#include "../cpu/pic.h"

void kernel_main(void){
	isr_install();
	enable_cursor(0, 15);
	clear_screen();

	asm volatile("int 100");
}