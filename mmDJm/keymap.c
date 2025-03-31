#include QMK_KEYBOARD_H
#include "version.h"
#include "i18n.h"
#include "keymap_us_international.h"
#define MOON_LED_LEVEL LED_LEVEL
#define ML_SAFE_RANGE SAFE_RANGE

enum custom_keycodes {
  // RGB
  RGB_SLD = ML_SAFE_RANGE,

  // Layer0 - Row0
  L0_HASH, L0_ONE, L0_TWO, L0_THREE, L0_FOUR, L0_FIVE, L0_SIX, L0_SEVEN, L0_EIGHT, L0_NINE, L0_ZERO, L0_DOLAR,
  // Layer0 - Row1
  L0_AT, L0_AGRAV, L0_EGRAV, L0_QUOTE,
  // Layer0 - Row2
  L0_COMMA, L0_CIRC,
  // Layer0 - Row3
  L0_DOT, L0_C
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_moonlander(
        L0_HASH, L0_ONE, L0_TWO, L0_THREE, L0_FOUR, L0_FIVE, KC_NO, KC_NO, L0_SIX, L0_SEVEN, L0_EIGHT, L0_NINE, L0_ZERO, L0_DOLAR,
        L0_AT, L0_AGRAV, KC_J, KC_O, US_EACU, KC_B, KC_NO, KC_NO, KC_F, KC_D, KC_L, L0_QUOTE, KC_Q, KC_X,
        KC_LEFT_SHIFT, KC_A, KC_I, KC_E, KC_U, L0_COMMA, KC_NO, KC_NO, KC_P, KC_T, KC_S, KC_R, KC_N, L0_CIRC,
        KC_ESCAPE, KC_K, KC_Y, L0_EGRAV, L0_DOT, KC_W, KC_G, L0_C, KC_M, KC_H, KC_V, KC_Z,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_SPACE, KC_TAB, KC_NO, KC_NO, KC_BSPC, KC_ENTER),
};

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = {{131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {0, 0, 0}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {0, 0, 0}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {0, 0, 0}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {0, 0, 0}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {0, 0, 0}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {131, 255, 255}, {131, 255, 255}, {0, 0, 0}, {0, 0, 0}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {0, 0, 0}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {0, 0, 0}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {0, 0, 0}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {0, 0, 0}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {0, 0, 0}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {131, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {131, 255, 255}, {131, 255, 255}, {0, 0, 0}, {0, 0, 0}},

};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
        .h = pgm_read_byte(&ledmap[layer][i][0]),
        .s = pgm_read_byte(&ledmap[layer][i][1]),
        .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
      rgb_matrix_set_color(i, 0, 0, 0);
    } else {
      RGB rgb = hsv_to_rgb(hsv);
      float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
      rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  if (rawhid_state.rgb_control) {
    return false;
  }
  if (keyboard_config.disable_layer_led) {
    return false;
  }
  switch (biton32(layer_state)) {
  case 0:
    set_layer_color(0);
    break;
  default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t mod_state = get_mods();
  bool mod_circ = false;
  bool mod_trem = false;

  switch (keycode) {
  case L0_HASH:
    if (record->event.pressed) {
      if (mod_state & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(US_PERC);
        set_mods(mod_state);
      } else {
        tap_code16(US_HASH);
      }
    }
    break;
  case L0_ONE:
    if (record->event.pressed) {
      if (mod_state & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(KC_1);
        set_mods(mod_state);
      } else {
        SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_7) SS_TAP(X_KP_1)));
      }
    }
    break;
  case L0_TWO:
    if (record->event.pressed) {
      if (mod_state & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(KC_2);
        set_mods(mod_state);
      } else {
        SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_8) SS_TAP(X_KP_7)));
      }
    }
    break;
  case L0_THREE:
    if (record->event.pressed) {
      if (mod_state & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(KC_3);
        set_mods(mod_state);
      } else {
        tap_code16(S(KC_QUOTE));
        tap_code16(KC_SPACE);
      }
    }
    break;
  case L0_FOUR:
    if (record->event.pressed) {
      if (mod_state & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(KC_4);
        set_mods(mod_state);
      } else {
        tap_code16(KC_MINUS);
      }
    }
    break;
  case L0_FIVE:
    if (record->event.pressed) {
      if (mod_state & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(KC_5);
        set_mods(mod_state);
      }
      else {
        tap_code16(US_PLUS);
      }
    }
    break;
  case L0_SIX:
    if (record->event.pressed) {
      if (mod_state & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(KC_6);
        set_mods(mod_state);
      } else {
        tap_code16(US_ASTR);
      }
    }
    break;
  case L0_SEVEN:
    if (record->event.pressed) {
      if (mod_state & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(KC_7);
        set_mods(mod_state);
      } else {
        tap_code16(KC_SLASH);
      }
    }
    break;
  case L0_EIGHT:
    if (record->event.pressed) {
      if (mod_state & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(KC_8);
        set_mods(mod_state);
      } else {
        tap_code16(KC_EQUAL);
      }
    }
    break;
  case L0_NINE:
    if (record->event.pressed) {
      if (mod_state & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(KC_9);
        set_mods(mod_state);
      } else {
        tap_code16(US_LPRN);
      }
    }
    break;
  case L0_ZERO:
    if (record->event.pressed) {
      if (mod_state & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(KC_0);
        set_mods(mod_state);
      } else {
        tap_code16(US_RPRN);
      }
    }
    break;
  case L0_DOLAR:
    if (record->event.pressed) {
      if (mod_state & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(US_EURO);
        set_mods(mod_state);
      } else {
        tap_code16(US_DLR);
      }
    }
    break;
  case L0_AT:
    if (record->event.pressed) {
      if (mod_state & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(US_UNDS);
        set_mods(mod_state);
      } else {
        tap_code16(KC_AT);
      }
    }
    break;
  case L0_AGRAV:
    if (record->event.pressed) {
      if (mod_state & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(KC_GRV);
        set_mods(mod_state);
        tap_code16(KC_A);
      } else {
        tap_code16(KC_GRV);
        tap_code16(KC_A);
      }
    }
    break;
  case L0_EGRAV:
    if (record->event.pressed) {
      if (mod_state & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(KC_GRV);
        set_mods(mod_state);
        tap_code16(KC_E);
      } else {
        tap_code16(KC_GRV);
        tap_code16(KC_E);
      }
    }
    break;
  case L0_QUOTE:
    if (record->event.pressed) {
      if (mod_state & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(US_QUES);
        set_mods(mod_state);
      } else {
        tap_code16(KC_QUOTE);
        tap_code16(KC_SPACE);
      }
    }
    break;
  case L0_COMMA:
    if (record->event.pressed) {
      if (mod_state & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(KC_SCLN);
        set_mods(mod_state);
      } else {
        tap_code16(KC_COMM);
      }
    }
    break;
  case L0_CIRC:
    if (record->event.pressed) {
      if (mod_state & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(US_EXLM);
        set_mods(mod_state);
      } else {
        if(mod_circ) {
          mod_circ = false;
          mod_trem = true;
        } else {
          mod_circ = true;
        }
      }
    }
    break;
  case L0_DOT:
    if (record->event.pressed) {
      if (mod_state & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(US_COLN);
        set_mods(mod_state);
      } else {
        tap_code16(KC_DOT);
      }
    }
    break;
  case L0_C:
  if(record->event.pressed) {
    if (mod_state & MOD_MASK_SHIFT) {
      del_mods(MOD_MASK_SHIFT);
      if(mod_circ) {
        tap_code16(S(US_CCED));
      } else {
        tap_code16(S(KC_C));
      }
      set_mods(mod_state);
    } else {
      if(mod_circ) {
        tap_code16(US_CCED);
      } else {
        tap_code16(KC_C);
      }
    }
  }

  case RGB_SLD:
    if (rawhid_state.rgb_control) {
      return false;
    }
    if (record->event.pressed) {
      rgblight_mode(1);
    }
    return false;
  }
  return true;
}
