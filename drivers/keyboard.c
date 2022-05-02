#include <stdint.h>
#include <stdbool.h>
#include "keyboard.h"
#include "screen.h"
#include "cpu/x86.h"
#include "cpu/isr.h"
#include "cpu/pic.h"
#include "util/util.h"

#define EXTENDED_SCANCODE (0xE0)
#define KEYBOARD_DATA (0x60)

static void (*kernel_callback)(uint8_t);
static bool enabled = false;

/* scancodes can be used as indices into this array, extended scancodes need to be handled seperately */
static const uint8_t v_keycodes[] = {VK_RES, VK_ESC, VK_1, VK_2, VK_3, VK_4, VK_5, VK_6, VK_7, VK_8, VK_9, VK_0,
VK_SZ, VK_ACCENT, VK_BACK, VK_TAB, VK_Q, VK_W, VK_E, VK_R, VK_T, VK_Z, VK_U, VK_I, VK_O, VK_P, VK_UE, VK_PLUS,
VK_ENTER, VK_LCTRL, VK_A, VK_S, VK_D, VK_F, VK_G, VK_H, VK_J, VK_K, VK_L, VK_OE, VK_CIRCUMFLEX, VK_LSHIFT, VK_HASH,
VK_Y, VK_X, VK_C, VK_V, VK_B, VK_N, VK_M, VK_COMMA, VK_DOT, VK_MINUS, VK_RSHIFT, VK_MULT, VK_LALT, VK_SPACE,
VK_SPACE, VK_CAPS_LOCK, VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10, VK_NUM_LOCK, VK_SCROLL_LOCK,
VK_HOME_NUM7, VK_UP_NUM8, VK_PAGE_UP_NUM2, VK_SUB, VK_LEFT_NUM4, VK_NUM5, VK_RIGHT_NUM6, VK_ADD, VK_END_NUM1,
VK_DOWN_NUM2, VK_PAGE_DOWN_NUM3, VK_INSERT_NUM0, VK_DELETE_NUMCOM, VK_PRINT_SCREEN, VK_RES, VK_LT, VK_F11, VK_F12};


/* convert scancodes to virtual keycodes that are passed to the kernel */
uint8_t to_vkey(uint16_t scancode){
	if (scancode & EXTENDED_SCANCODE){
		switch (scancode & !EXTENDED_SCANCODE){
			case 0x38:
				return VK_RALT;
			case 0x1C:
				return VKEXT_ENTER;
			case 0x1D:
				return VK_RCTRL;
			case 0x35:
				return VKEXT_DIV;
			case 0x47:
				return VKEXT_HOME;
			case 0x48:
				return VKEXT_UP;
			case 0x49:
				return VKEXT_PAGE_UP;
			case 0x4B:
				return VKEXT_LEFT;
			case 0x4D:
				return VKEXT_RIGHT;
			case 0x4F:
				return VKEXT_END;
			case 0x50:
				return VKEXT_DOWN;
			case 0x51:
				return VKEXT_PAGE_DOWN;
			case 0x52:
				return VKEXT_INSERT;
			case 0x53:
				return VKEXT_DELETE;
		}
	}
	return v_keycodes[scancode];
}

/* https://kbdlayout.info/kbdgr/scancodes+text?arrangement=ISO105 */
void keyboard_handler(registers *regs){
	UNUSED(regs);
	uint16_t scancode = inb(KEYBOARD_DATA);

	if (!enabled)
		return;

	/* if scancode is 0xE0 (extended), the next scancode/interrupt belongs to the same key stroke */
	static bool extended = false;
	if (extended){
		extended = false;
		scancode += EXTENDED_SCANCODE << 8;
	}else if (scancode == EXTENDED_SCANCODE){
		extended = true;
		return;
	}

	uint8_t vkey;
	if (scancode & 0x80){
		/* if key released, remove release bit(7) for to_vkey() and again */
		scancode &= ~0x80;
		vkey = to_vkey(scancode) | 0x80;
	}else{
		vkey = to_vkey(scancode);
	}
	kernel_callback(vkey);
}

void keyboard_enable(void){
	enabled = true;
}

void keyboard_disable(void){
	enabled = false;
}

#define PS2_COMMAND (0x64)
#define PORT1_ENABLE (0xAE)
#define SCANCODE_SET (0xF0)
#define SCANCODE_SET_2 (0x2)

void keyboard_init(void (*callback)(uint8_t vkey)){
	outb(PS2_COMMAND, PORT1_ENABLE);
	/* set scancode set 2 */
	outb(KEYBOARD_DATA, SCANCODE_SET);
	outb(KEYBOARD_DATA, SCANCODE_SET_2);
	/* clear keyboard output */
	inb(KEYBOARD_DATA);
	inb(KEYBOARD_DATA);
	inb(KEYBOARD_DATA);
	register_irq_handler(PIC_KEYBOARD, keyboard_handler);
	kernel_callback = callback;
	irq_enable(PIC_KEYBOARD);
}