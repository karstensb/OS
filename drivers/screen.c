#include "screen.h"
#include "../cpu/port.h"
#include "../libc/string.h"

static size_t cursor_offset;
static uint8_t terminal_color = VGA_COLOR_WHITE | VGA_COLOR_BLACK << 4;

static inline size_t get_offset(size_t col, size_t row) {return 2 * (row * VGA_WIDTH + col);}
static inline size_t get_offset_row(size_t offset){return offset / (2 * VGA_WIDTH);}
static inline size_t get_offset_col(size_t offset){return (offset - (get_offset_row(offset)*2*VGA_WIDTH))/2;}

static void update_cursor(){
	uint16_t offset = cursor_offset / 2;
	outb(REG_SCREEN_CTRL, 0x0F);
	outb(REG_SCREEN_DATA, (uint8_t) (offset & 0xFF));
	outb(REG_SCREEN_CTRL, 0x0E);
	outb(REG_SCREEN_DATA, (uint8_t) ((offset >> 8) & 0xFF));
}

void kprint(const char *msg){
	for (int i = 0; msg[i]; ++i){
		size_t row = get_offset_row(cursor_offset);
		size_t col = get_offset_col(cursor_offset);
		kprint_c_at(msg[i], row, col);
	}
	update_cursor();
}

void kprint_c(const char c){
	size_t row = get_offset_row(cursor_offset);
	size_t col = get_offset_col(cursor_offset);
	kprint_c_at(c, row, col);
	update_cursor();
}

void kprint_c_at(const char c, size_t row, size_t col){
	if (row > VGA_HEIGHT || col > VGA_WIDTH)
		return;
	size_t offset = get_offset(col, row);
	cursor_offset = offset;
	uint8_t *vidmem = (uint8_t *) VGA_MEM;
	if (cursor_offset >= 2 * VGA_HEIGHT * VGA_WIDTH){
		scroll_screen(1);
		cursor_offset -= VGA_WIDTH * 2;
	}
	if (c == '\n'){
		cursor_offset += (VGA_WIDTH*2) - get_offset_col(cursor_offset) -1;
	}else if (c == '\b'){
		vidmem[cursor_offset] = ' ';
		vidmem[cursor_offset+1] = terminal_color;
		cursor_offset -= 2;
		vidmem[cursor_offset] = '\b';
		vidmem[cursor_offset - 1] = terminal_color;
	}else{
		vidmem[cursor_offset] = c;
		vidmem[cursor_offset+1] = terminal_color;
		cursor_offset += 2;
	}

}

void clear_screen(){
	outb(REG_GRAPH_CTRL, MISC_GRAPH_REG);
	outb(REG_GRAPH_DATA, MEM_RANGE_B8000);
	for (int i = 0; i <= VGA_HEIGHT; ++i){
		for (int j = 0; j<= VGA_WIDTH; ++j){
			uint8_t *vid_mem = (uint8_t *) VGA_MEM;
			size_t offset = get_offset(j, i);
			vid_mem[offset] = 0;
			vid_mem[offset+1] = terminal_color;
		}
	}
	cursor_offset = 0;
	update_cursor();
}

void set_terminal_color(const enum vga_color foreground, const enum vga_color background){
	terminal_color = foreground | background << 4;
}

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end){
	outb(REG_SCREEN_CTRL, CURSOR_START);
	outb(REG_SCREEN_DATA, /* (inb(REG_SCREEN_CTRL) & 0xC0) |  */cursor_start);
	outb(REG_SCREEN_CTRL, CURSOR_END);
	outb(REG_SCREEN_DATA, /* (inb(REG_SCREEN_CTRL) & 0xE0) |  */cursor_end); 
}

void disable_cursor(){
	outb(REG_SCREEN_CTRL, CURSOR_START);
	outb(REG_SCREEN_DATA, CURSOR_DISABLE);
}

void scroll_screen(size_t rows){
	memcpy((void *) (rows*VGA_WIDTH*2 + VGA_MEM), (void *) VGA_MEM, (VGA_WIDTH*VGA_HEIGHT - rows*VGA_WIDTH)*2);
	uint8_t *ptr = (uint8_t *) VGA_MEM + (VGA_WIDTH*VGA_HEIGHT - rows*VGA_WIDTH) * 2;
	for (int i = 0; i < rows * VGA_WIDTH * 2; ++i){
		ptr[i] = ' ';
		ptr[++i] = terminal_color;
	}
}
