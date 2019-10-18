#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x2341
#define PRODUCT_ID      0x8036
#define DEVICE_VER      0x0001
#define MANUFACTURER    Leo Soundmonster
#define PRODUCT         rabimmel
#define DESCRIPTION     SK6812 Controller with a keypad

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 3

/* key matrix pins */
#define MATRIX_ROW_PINS { D0, D4, C6, C7 }
#define MATRIX_COL_PINS { E6, B4, B5 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Locking resynchronize hack */
// #define LOCKING_RESYNC_ENABLE

