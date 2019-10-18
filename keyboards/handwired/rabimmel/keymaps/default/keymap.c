#include QMK_KEYBOARD_H


enum layers {
  NORMAL_LAYER = 0
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [NORMAL_LAYER]= LAYOUT(
	KC_1, KC_2, KC_3,
	KC_4, KC_5, KC_6,
	KC_7, KC_8, KC_9,
	RESET,KC_0, KC_SPC
    ),
};


/* DISABLED
void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}
*/

/*
layer_state_t layer_state_set_user(layer_state_t state)
{
    turn_off_leds();

    switch (biton32(state))
    {
    case NORMAL_LAYER:
	break;

    case MEDIA_LAYER:
	turn_on_led(RED_LED);
	break;

    case TBD_LAYER2:
	turn_on_led(BLUE_LED);
	break;

    case TBD_LAYER3:
	turn_on_led(GREEN_LED);
	break;
	}
    return state;
}
*/
