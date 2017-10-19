#ifndef KEYCODE_H
#define KEYCODE_H

#include <stdint.h>
#include "core/math.h"

enum {
  K_UNKNOWN,

  K_SPACE = 32,
  K_CAPSLOCK = 127,
  K_RETURN,
  K_ESCAPE,
  K_BACKSPACE,
  K_TAB,
  K_PAGEUP,
  K_PAGEDOWN,
  K_DELETE,
  K_RIGHT,
  K_LEFT,
  K_DOWN,
  K_UP,
  K_LCTRL,
  K_LSHIFT,
  K_LALT,
  K_LGUI,
  K_RCTRL,
  K_RSHIFT,
  K_RALT,
  K_RGUI,
  K_CONSOLE,
  K_F1,
  K_F2,
  K_F3,
  K_F4,
  K_F5,
  K_F6,
  K_F7,
  K_F8,
  K_F9,
  K_F10,
  K_F11,
  K_F12,
  K_F13,
  K_F14,
  K_F15,
  K_F16,
  K_F17,
  K_F18,
  K_F19,
  K_F20,
  K_F21,
  K_F22,
  K_F23,
  K_F24,

  K_MOUSE1,
  K_MOUSE2,
  K_MOUSE3,
  K_MOUSE4,
  K_MOUSE5,
  K_MWHEELUP,
  K_MWHEELDOWN,

  /* for convenience, these are in the same order as the maple button enum */
  K_CONT_C,
  K_CONT_B,
  K_CONT_A,
  K_CONT_START,
  K_CONT_DPAD_UP,
  K_CONT_DPAD_DOWN,
  K_CONT_DPAD_LEFT,
  K_CONT_DPAD_RIGHT,
  K_CONT_Z,
  K_CONT_Y,
  K_CONT_X,
  K_CONT_D,
  K_CONT_DPAD2_UP,
  K_CONT_DPAD2_DOWN,
  K_CONT_DPAD2_LEFT,
  K_CONT_DPAD2_RIGHT,
  K_CONT_JOYX_NEG,
  K_CONT_JOYX_POS,
  K_CONT_JOYY_NEG,
  K_CONT_JOYY_POS,
  K_CONT_LTRIG,
  K_CONT_RTRIG,

  K_NUM_KEYS
};

/* keyboard input callbacks are passed a key and a value which can represent
   either a digital button press, or an analog key / axis movement. analog
   sources are split into individual positive / negative keys, with a 16-bit
   unsigned integer for a value */
#define KEY_UP 0
#define KEY_DOWN UINT16_MAX

static inline int axis_s16_to_u16(int16_t value, uint16_t *out) {
  if (value < 0) {
    /* scale from [INT16_MIN, 0] to [UINT16_MAX, 0] */
    *out = (uint16_t)MIN(-(int32_t)value * 2, UINT16_MAX);
    return 0;
  }

  /* scale from [0, INT16_MAX] to [0, UINT16_MAX] */
  *out = (uint16_t)((int32_t)value * 2);
  return 1;
}

static inline uint8_t axis_neg_u16_to_u8(uint16_t value) {
  /* scale from [0, UINT16_MAX] to [127, 0] */
  return 127 - (value >> 9);
}

static inline uint8_t axis_pos_u16_to_u8(uint16_t value) {
  /* scale from [0, UINT16_MAX] to [128, 255] */
  return 128 + (value >> 9);
}

static inline uint8_t axis_u16_to_u8(uint16_t value) {
  /* scale from [0, UINT16_MAX] to [0, 255] */
  return value >> 7;
}

int get_key_by_name(const char *keyname);
const char *get_name_by_key(int key);

#endif
