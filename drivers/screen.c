#include "screen.h"
#include "cpu/x86.h"
#include "util/string.h"

#define VGA_WIDTH (80)
#define VGA_HEIGHT (25)
#define VGA_MEM (0xB8000)
#define REG_GRAPH_CTRL (0x03CE)
#define REG_GRAPH_DATA (0x03CF)
#define MISC_GRAPH_REG (0x06)
#define MEM_RANGE_B8000 (0x0C)
#define REG_SCREEN_CTRL (0x3D4)
#define REG_SCREEN_DATA (0x3D5)
#define CURSOR_START (0x0A)
#define CURSOR_END (0x0B)
#define CURSOR_DISABLE (0x20)

static size_t cursor_offset;
static uint8_t terminal_color = VGA_COLOR_WHITE | VGA_COLOR_BLACK << 4;

static inline size_t get_offset(size_t col, size_t row) {return row * VGA_WIDTH + col;}
static inline size_t get_offset_row(size_t offset) {return offset / VGA_WIDTH;}
static inline size_t get_offset_col(size_t offset) {return offset - (get_offset_row(offset) * VGA_WIDTH);}

static void update_cursor(){
	outb(REG_SCREEN_CTRL, 0x0F);
	outb(REG_SCREEN_DATA, (uint8_t) (cursor_offset & 0xFF));
	outb(REG_SCREEN_CTRL, 0x0E);
	outb(REG_SCREEN_DATA, (uint8_t) ((cursor_offset >> 8) & 0xFF));
}


void kprint(const char *msg){
	for (int i = 0; msg[i]; ++i){
		size_t row = get_offset_row(cursor_offset);
		size_t col = get_offset_col(cursor_offset);
		kprintc_at(msg[i], row, col);
	}
	update_cursor();
}

void kprintc(const char c){
	size_t row = get_offset_row(cursor_offset);
	size_t col = get_offset_col(cursor_offset);
	kprintc_at(c, row, col);
	update_cursor();
}

void kprinti(int32_t i, int base){
	char buffer[32];
	kprint(itoa(i, buffer, base));
}

void kprintc_at(const char c, size_t row, size_t col){
	if (row > VGA_HEIGHT || col > VGA_WIDTH)
		return;
	cursor_offset = get_offset(col, row);
	uint16_t *vidmem = (uint16_t *) VGA_MEM;
	if (cursor_offset >= VGA_HEIGHT * VGA_WIDTH){
		scroll_screen(1);
		cursor_offset -= VGA_WIDTH;
	}
	if (c == '\n'){
		cursor_offset += VGA_WIDTH - get_offset_col(cursor_offset);
	}else if (c == '\b'){
		vidmem[cursor_offset] = (terminal_color << 8) | 0;
		--cursor_offset;
		vidmem[cursor_offset] = (terminal_color << 8) | '\b';
	}else{
		vidmem[cursor_offset] = (terminal_color << 8) | c;
		++cursor_offset;
	}

}

void clear_screen(){
	outb(REG_GRAPH_CTRL, MISC_GRAPH_REG);
	outb(REG_GRAPH_DATA, MEM_RANGE_B8000);
	for (int i = 0; i <= VGA_HEIGHT; ++i){
		for (int j = 0; j<= VGA_WIDTH; ++j){
			uint16_t *vid_mem = (uint16_t *) VGA_MEM;
			size_t offset = get_offset(j, i);
			vid_mem[offset] = (terminal_color << 8) | 0;
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
	outb(REG_SCREEN_DATA, cursor_start);
	outb(REG_SCREEN_CTRL, CURSOR_END);
	outb(REG_SCREEN_DATA, cursor_end); 
}

void disable_cursor(){
	outb(REG_SCREEN_CTRL, CURSOR_START);
	outb(REG_SCREEN_DATA, CURSOR_DISABLE);
}

void scroll_screen(size_t rows){
	memmove((void *) VGA_MEM, (void *) (rows*VGA_WIDTH*2 + VGA_MEM), (VGA_WIDTH*VGA_HEIGHT - rows*VGA_WIDTH)*2);
	uint16_t *ptr = (uint16_t *) VGA_MEM + (VGA_WIDTH*VGA_HEIGHT - rows*VGA_WIDTH);
	for (int i = 0; i < (int) rows * VGA_WIDTH; ++i){
		ptr[i] = (terminal_color << 8) | 0;
	}
}
