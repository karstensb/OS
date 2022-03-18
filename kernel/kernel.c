#include "../drivers/screen.h"
#include "../cpu/port.h"
#include "../libc/string.h"

void kernel_main(void){
	enable_cursor(0, 15);
	clear_screen();
}