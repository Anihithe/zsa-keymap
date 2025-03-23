#include QMK_KEYBOARD_H
#include "version.h"
#include "i18n.h"
#define MOON_LED_LEVEL LED_LEVEL
#define ML_SAFE_RANGE SAFE_RANGE

enum custom_keycodes {
  // RGB
  RGB_SLD = ML_SAFE_RANGE,

  // MACRO
  ST_MACRO_0,
  ST_MACRO_1,

  // CUSTOM KC
  ST_MACRO_AGRAV,
  ST_MACRO_ECIRC
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_moonlander(
    US_HASH,        ST_MACRO_0,     ST_MACRO_1,     CT_DQOT,        KC_MINUS,       US_PLUS,        KC_NO,                                          KC_NO,          US_ASTR,        KC_SLASH,       KC_EQUAL,       US_LPRN,        US_RPRN,        US_DLR,         
    KC_AT,          ST_MACRO_AGRAV, KC_J,           KC_O,           US_EACU,        KC_B,           KC_NO,                                          KC_NO,          KC_F,           KC_D,           KC_L,           KC_QUOTE,       KC_Q,           KC_X,           
    KC_TRANSPARENT, KC_A,           KC_I,           KC_E,           KC_U,           KC_COMMA,       KC_NO,                                                                          KC_NO,          KC_P,           KC_T,           KC_S,           KC_R,           KC_N,           US_CIRC,        
    KC_ESCAPE,      KC_K,           KC_Y,           ST_MACRO_ECIRC, KC_DOT,         KC_W,                                           KC_G,           KC_C,           KC_M,           KC_H,           KC_V,           KC_W,           
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                                                                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    KC_SPACE,       KC_TAB,         KC_NO,                          KC_NO,          KC_BSPC,        KC_ENTER
  ),
};

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}


const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = { {131,255,255}, {131,255,255}, {131,255,255}, {131,255,255}, {0,0,0}, {131,255,255}, {131,255,255}, {131,255,255}, {131,255,255}, {0,0,0}, {131,255,255}, {131,255,255}, {131,255,255}, {131,255,255}, {0,0,0}, {131,255,255}, {131,255,255}, {131,255,255}, {131,255,255}, {0,0,0}, {131,255,255}, {131,255,255}, {131,255,255}, {131,255,255}, {0,0,0}, {131,255,255}, {131,255,255}, {131,255,255}, {131,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {131,255,255}, {131,255,255}, {0,0,0}, {0,0,0}, {131,255,255}, {131,255,255}, {131,255,255}, {131,255,255}, {0,0,0}, {131,255,255}, {131,255,255}, {131,255,255}, {131,255,255}, {0,0,0}, {131,255,255}, {131,255,255}, {131,255,255}, {131,255,255}, {0,0,0}, {131,255,255}, {131,255,255}, {131,255,255}, {131,255,255}, {0,0,0}, {131,255,255}, {131,255,255}, {131,255,255}, {131,255,255}, {0,0,0}, {131,255,255}, {131,255,255}, {131,255,255}, {131,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {131,255,255}, {131,255,255}, {0,0,0}, {0,0,0} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );   
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  if (rawhid_state.rgb_control) {
      return false;
  }
  if (keyboard_config.disable_layer_led) { return false; }
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
  mod_state = get_mods();
  switch (keycode) {

    //MACRO
    case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_7) SS_TAP(X_KP_1) ));
    }
    break;
    case ST_MACRO_1:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_8) SS_TAP(X_KP_7) ));
    }
    break;
    case ST_MACRO_AGRAV:
      if(record->event.pressed) {
        if (mod_state & MOD_MASK_SHIFT) {
          SEND_STRING(SS_TAP(X_GRV) SS_LSFT(SS_TAP(X_A)))
        } else {
          SEND_STRING(SS_TAP(X_GRV) SS_TAP(X_A));
        }
      }
      break;
    case ST_MACRO_ECIRC:
      if(record->event.pressed) {
        if (mod_state & MOD_MASK_SHIFT) {
          SEND_STRING(SS_TAP(X_QUOTE) SS_LSFT(SS_TAP(X_E)))
        } else {
          SEND_STRING(SS_TAP(X_QUOTE) SS_TAP(X_E))
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



