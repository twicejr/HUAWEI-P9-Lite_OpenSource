#ifndef _K3_KEYPAD_H_
#define _K3_KEYPAD_H_
#include <linux/input/matrix_keypad.h>

#define DPAD_CENTER 232

#define KEYPAD_CHECK_KEYCODE(map, keycode) (map[(keycode) >> 4] & (1 << ((keycode) & 0x0F)))
#define KEYPAD_SET_KEYCODE(map, keycode) (map[(keycode) >> 4] |= (1 << ((keycode) & 0x0F)))
#define KEYPAD_CLR_KEYCODE(map, keycode) (map[(keycode) >> 4] &= ~(1 << ((keycode) & 0x0F)))


struct k3v2_keypad_platdata {
	struct matrix_keymap_data	*keymap_data;
	struct keypad_remap			*keypad_remap;
	unsigned int				rows;
	unsigned int               	cols;
	unsigned int               	row_shift;
};

/*
 * target_keycode: target keycode remapped to
 * keynum        : number of keycodes to remap
 * delay         : timeout for pending
 */
struct keypad_remap_item {
	uint16_t target_keycode;
	uint16_t keynum;
	uint16_t delay;
	uint16_t *keycodes;
};

struct keypad_remap_state {
	bool pending;
	bool remapped;
	unsigned int time;
	unsigned char down_state;
};

struct keypad_remap {
	int count;
	struct keypad_remap_item *items;
};

#endif
