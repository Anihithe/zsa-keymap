//#include QMK_KEYBOARD_H
//#include "version.h"
#include "keymap_us_international.h"

#define MOON_LED_LEVEL LED_LEVEL
#define ML_SAFE_RANGE SAFE_RANGE


void ckc_hash(void) {
    if (record->event.pressed)
    {
      if (mod_state & MOD_MASK_SHIFT)
      {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(US_PERC);
        set_mods(mod_state);
      }
      else
      {
        tap_code16(US_HASH);
      }
    }
}