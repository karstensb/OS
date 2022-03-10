#ifndef SCREEN_H
#define SCREEN_H

#include <stddef.h>
#include <stdint.h>

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

typedef enum vga_color{
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
}vga_color;

void kprint(const char *msg);
void kprint_c(const char c);
void kprint_c_at(const char c, size_t row, size_t col);
void clear_screen();
void set_terminal_color(const enum vga_color foreground, const enum vga_color background);
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void disable_cursor();
void scroll_screen(size_t rows);

#endif /* SCREEN_H */