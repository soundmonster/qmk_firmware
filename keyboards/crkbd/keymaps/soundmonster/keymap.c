#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

#ifdef OLED_DRIVER_ENABLE
static uint32_t oled_timer = 0;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

// Custom keycodes for layer keys
// Dual function escape with left command
#define KC_LGESC LGUI_T(KC_ESC)
// Dual function escape with left option
#define KC_LAESC LALT_T(KC_ESC)

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------.                ,---------------------------------------------.
     KC_TAB,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                   KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,  KC_BSPC,\
  //|------+------+------+------+------+------|                |------+------+-------+------+-------+--------|
    KC_LGUI,  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,                   KC_H,  KC_J,  KC_K,  KC_L, KC_SCLN,KC_QUOT,\
  //|------+------+------+------+------+------|                |------+------+-------+------+-------+--------|
    KC_LSPO,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,                   KC_N,  KC_M,KC_COMM,KC_DOT,KC_SLSH,KC_RSPC,\
  //|------+------+------+------+------+------+------|  |------+------+------+---0---+------+-------+--------|
                               KC_LAESC,LOWER, KC_SPC,  KC_ENT, RAISE, KC_RCTL \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT( \
  //,---------------------------------------------.                ,-----------------------------------------.
     KC_ESC,  KC_1, KC_2,   KC_3,   KC_4,   KC_5,                    KC_6,  KC_7,  KC_8,  KC_9,  KC_0, KC_DEL,\
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    KC_LGUI, KC_NO,KC_MS_L,KC_MS_D,KC_MS_U,KC_MS_R,                KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT,KC_NO,KC_NO,\
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    KC_LSFT, KC_NO,KC_BTN2,KC_WH_D,KC_WH_U,KC_BTN1,                KC_HOME,KC_PGDN,KC_PGUP,KC_END,KC_NO,KC_NO,\
  //|------+------+-------+-------+-------+-------+------|  |------+------+------+------+------+------+------|
                                    KC_LALT, LOWER,KC_SPC,   KC_ENT, RAISE,KC_RCTL \
                                  //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
     KC_ESC,KC_EXLM,KC_AT,KC_HASH,KC_DLR,KC_PERC,              KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_LGUI, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                KC_MINS,KC_EQL,KC_LCBR,KC_RCBR,KC_PIPE,KC_GRV,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_LSFT, KC_F6, KC_F7, KC_F8, KC_F9,KC_F10,                KC_UNDS,KC_PLUS,KC_LBRC,KC_RBRC,KC_BSLS,KC_TILD,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                KC_LALT, LOWER,KC_SPC,   KC_ENT, RAISE,KC_RCTL \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
      RESET,RGBRST, KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO,KC__MUTE, KC_NO, KC_NO, KC_NO, KC_NO,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    RGB_TOG,RGB_HUI,RGB_SAI,RGB_VAI,KC_NO,KC_NO,               KC_PAUSE,KC__VOLUP, KC_NO, KC_NO, KC_NO, KC_NO,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    RGB_MOD,RGB_HUD,RGB_SAD,RGB_VAD,KC_NO,KC_NO,               KC_SCROLLLOCK,KC__VOLDOWN, KC_NO, KC_NO, KC_NO, KC_NO,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                KC_LGUI, LOWER,KC_SPC,   KC_ENT, RAISE,KC_RALT \
                              //`--------------------'  `--------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_layer_state(void) {
    oled_write_P(PSTR("Layer"), false);
    oled_write_P(PSTR("RAISE"), layer_state_is(_RAISE));
    oled_write_P(PSTR(" BASE"), layer_state_is(_QWERTY));
    oled_write_P(PSTR("LOWER"), layer_state_is(_LOWER));
    oled_write_P(PSTR("ADJST"), layer_state_is(_ADJUST));
}

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("Mods:"), false);
    oled_write_P(PSTR("SHIFT"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR(" CTRL"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR(" OPT "), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR(" CMD "), (modifiers & MOD_MASK_GUI));
}

void render_status_main(void) {
    /* Show Keyboard Layout  */
    render_layer_state();
    render_space();
    render_mod_status(get_mods()|get_oneshot_mods());
}

void render_status_secondary(void) {
    /* Show Keyboard Layout  */
    render_layer_state();
    render_space();
    render_mod_status(get_mods()|get_oneshot_mods());
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 30000) {
        oled_off();
        return;
    }
#ifndef SPLIT_KEYBOARD
    else { oled_on(); }
#endif

    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}

#endif
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}
