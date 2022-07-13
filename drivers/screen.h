#pragma once

#include <stddef.h>
#include <stdint.h>

#define CURSOR_MIN (0)
#define CURSOR_MAX (15)
#define VGA_WIDTH (80)
#define VGA_HEIGHT (25)

enum vga_color{
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
};

void kprint(const char *msg);
void kprintc(const char c);
void kprinti(int32_t i, int base);
void kprintc_at(const char c, size_t row, size_t col);
void clear_screen(char c);
void set_terminal_color(const enum vga_color foreground, const enum vga_color background);
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void disable_cursor(void);
void scroll_screen(size_t rows);