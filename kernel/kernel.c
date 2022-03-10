#include "../drivers/screen.h"
#include "../cpu/port.h"
#include "../libc/string.h"

void kernel_main(void){
	enable_cursor(0, 15);
	clear_screen();
}


/* TODO:
 * fonts:  http://www.osdever.net/FreeVGA/vga/seqreg.htm
 * pages: change vga mem location https://wiki.osdev.org/Printing_To_Screen
 */ 