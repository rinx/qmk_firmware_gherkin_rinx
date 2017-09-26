/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#undef MATRIX_ROW_PINS
// USB on the left
#define MATRIX_ROW_PINS { B6, B2, B3, B1, F7 }
// USB on the right
// #define MATRIX_ROW_PINS { F7, B1, B3, B2, B6 }
#undef MATRIX_COL_PINS
// USB on the left
#define MATRIX_COL_PINS { D0, D4, C6, D7, E6, B4 }
// USB on the right
// #define MATRIX_COL_PINS { B4, E6, D7, C6, D4, D0 }
#undef UNUSED_PINS
#define UNUSED_PINS

#endif

#undef BACKLIGHT_LEVELS
#define BACKLIGHT_LEVELS 4

#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 0

#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 150

#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 3

#undef MOUSEKEY_MOVE_DELTA
#define MOUSEKEY_MOVE_DELTA 5

#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 0

#undef TAPPING_TERM
#define TAPPING_TERM 200

#define TAPPING_TOGGLE  1

#define PERMISSIVE_HOLD

