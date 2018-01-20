#include "gherkin.h"
#include "action_layer.h"
#include "eeconfig.h"

#define RKEYMAP( \
	 K00,   K01,   K02,   K03,   K04,   K05,   K10,   K11,   K12,   K13 , \
	 K14,   K15,   K20,   K21,   K22,   K23,   K24,   K25,   K30,   K31 , \
	 K32,   K33,   K34,   K35,   K40,   K41,   K42,   K43,   K44,   K45   \
) { \
	{ K45,   K44,   K43,   K42,   K41,   K40 }, \
	{ K35,   K34,   K33,   K32,   K31,   K30 }, \
	{ K25,   K24,   K23,   K22,   K21,   K20 }, \
	{ K15,   K14,   K13,   K12,   K11,   K10 }, \
	{ K05,   K04,   K03,   K02,   K01,   K00 }  \
}

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _RQWERTY 1
#define _LOWER 2
#define _RLOWER 3
#define _RAISE 4
#define _RRAISE 5
#define _FUNCT 6
#define _RFUNCT 7
#define _ARROW 8
#define _RARROW 9
#define _ADJUST 10
#define _RADJUST 11
#define _ADMINI 12
#define _RADMINI 13
#define _IJIDEA 14
#define _RIJIDEA 15

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define NEXTWKS ACTION_MODS_KEY(MOD_LCTL, KC_RGHT)
#define PREVWKS ACTION_MODS_KEY(MOD_LCTL, KC_LEFT)
#define NEXTTAB ACTION_MODS_KEY(MOD_LGUI, KC_RCBR)
#define PREVTAB ACTION_MODS_KEY(MOD_LGUI, KC_LCBR)
#define WINCOPY ACTION_MODS_KEY(MOD_LCTL, KC_C)
#define WINPASTE ACTION_MODS_KEY(MOD_LCTL, KC_V)
#define MACUNDO ACTION_MODS_KEY(MOD_LGUI, KC_Z)
#define MACREDO ACTION_MODS_KEY(MOD_LGUI | MOD_LSFT, KC_Z)
#define MACCUT ACTION_MODS_KEY(MOD_LGUI, KC_X)
#define MACCOPY ACTION_MODS_KEY(MOD_LGUI, KC_C)
#define MACPASTE ACTION_MODS_KEY(MOD_LGUI, KC_V)
#define MACFIND ACTION_MODS_KEY(MOD_LGUI, KC_F)
#define SPTLGHT ACTION_MODS_KEY(MOD_LGUI, KC_SPC)
#define MISSIONCTL ACTION_MODS_KEY(MOD_LCTL, KC_UP)
#define NEXTAPP ACTION_MODS_KEY(MOD_LGUI, KC_TAB)
#define PREVAPP ACTION_MODS_KEY(MOD_LGUI | MOD_LSFT, KC_TAB)

#define SCR_BR_UP KC_PAUS
#define SCR_BR_DOWN KC_SLCK

#define IDEA_O ACTION_MODS_KEY(MOD_LGUI | MOD_LSFT, KC_O)
#define IDEA_F ACTION_MODS_KEY(MOD_LGUI | MOD_LSFT, KC_F)
#define IDEA_R ACTION_MODS_KEY(MOD_LGUI | MOD_LSFT, KC_R)
#define IDEA_A ACTION_MODS_KEY(MOD_LGUI | MOD_LSFT, KC_A)
#define IDEA_BARF_BACK ACTION_MODS_KEY(MOD_LGUI |MOD_LCTL, KC_K)
#define IDEA_BARF_FORW ACTION_MODS_KEY(MOD_LGUI |MOD_LSFT, KC_J)
#define IDEA_SLURP_BACK ACTION_MODS_KEY(MOD_LGUI |MOD_LCTL, KC_J)
#define IDEA_SLURP_FORW ACTION_MODS_KEY(MOD_LGUI |MOD_LSFT, KC_K)
#define IDEA_CURSV_EVAL ACTION_MODS_KEY(MOD_LCTL |MOD_LSFT, KC_E)
#define IDEA_CURSV_LOAD ACTION_MODS_KEY(MOD_LCTL |MOD_LSFT, KC_M)
#define IDEA_CURSV_CHNS ACTION_MODS_KEY(MOD_LCTL |MOD_LSFT, KC_N)

// macros
#define SEND_KEYMAP_URI 0
#define MAC_COPY_PASTE 1
#define WIN_COPY_PASTE 2

// TAP DANCE
enum {
    TD_Q_ESC = 0,
    TD_W_TAB = 1,
    TD_Q_TAB,
    TD_P_SPL,
    TD_X_ALT,
    TD_C_GUI
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  RQWERTY,
  LOWER,
  RLOWER,
  RAISE,
  RRAISE,
  FUNCT,
  RFUNCT,
  ARROW,
  RARROW,
  ADJUST,
  RADJUST,
  ADMINI,
  RADMINI,
  IJIDEA,
  RIJIDEA,
  BACKLIT,
  DYNAMIC_MACRO_RANGE
};

#include "dynamic_macro.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,---------------------------------------------------------------------.
 * |TD_TAB|      |      |      |      |      |      |      |      |      |
 * |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      | Ctrl |
 * |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+-------------+------+------+------+------|
 * | Ctrl |  Alt |  GUI | Funct| Lower| Raise| Arrow|      |      | Shift|
 * |   Z  |   X  |   C  |   V  | Space|  BS  |   B  |   N  |   M  | Enter|
 * `---------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP( \
  TD(TD_Q_TAB), KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, \
  KC_A, KC_S, KC_D, KC_F, KC_G, \
  KC_H, KC_J, KC_K, KC_L, CTL_T(KC_SCLN), \
  CTL_T(KC_Z), ALT_T(KC_X), GUI_T(KC_C), LT(_FUNCT, KC_V), LT(_LOWER, KC_SPC), \
  LT(_RAISE, KC_BSPC), LT(_ARROW, KC_B), KC_N, KC_M, SFT_T(KC_ENT) \
),
[_RQWERTY] = RKEYMAP( \
  TD(TD_Q_TAB), KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, \
  KC_A, KC_S, KC_D, KC_F, KC_G, \
  KC_H, KC_J, KC_K, KC_L, CTL_T(KC_SCLN), \
  CTL_T(KC_Z), ALT_T(KC_X), GUI_T(KC_C), LT(_RFUNCT, KC_V), LT(_RLOWER, KC_SPC), \
  LT(_RRAISE, KC_BSPC), LT(_RARROW, KC_B), KC_N, KC_M, SFT_T(KC_ENT) \
),

/* Lower
 * ,---------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |
 * |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |
 * |   ~  |   "  |   ?  |   |  |      |      |   _  |   +  |   {  |   }  |
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |XXXXXX|      |      |      |      |      |
 * |      |      |      |      |XXXXXX|      |      |   <  |   >  |      |
 * `---------------------------------------------------------------------'
 */
[_LOWER] = KEYMAP( \
  KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, \
  KC_TILD, KC_DQUO, KC_QUES, KC_PIPE, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, \
  _______, _______, _______, _______, _______, _______, _______, KC_LABK, KC_RABK, _______ \
),
[_RLOWER] = RKEYMAP( \
  KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, \
  KC_TILD, KC_DQUO, KC_QUES, KC_PIPE, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, \
  _______, _______, _______, _______, _______, _______, _______, KC_LABK, KC_RABK, _______ \
),

/* Raise
 * ,---------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |
 * |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |
 * |   `  |   '  |   /  |   \  |      |      |   -  |   =  |   [  |   ]  |
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |XXXXXX|      |      |      |      |
 * |      |      |      |      |      |XXXXXX|   '  |   ,  |   .  |   \  |
 * `---------------------------------------------------------------------'
 */
[_RAISE] = KEYMAP( \
  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, \
  KC_GRV,  KC_QUOT, KC_SLSH, KC_BSLS, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, \
  _______, _______, _______, _______, _______, _______, _______, KC_COMM, KC_DOT, _______ \
),
[_RRAISE] = RKEYMAP( \
  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, \
  KC_GRV,  KC_QUOT, KC_SLSH, KC_BSLS, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, \
  _______, _______, _______, _______, _______, _______, _______, KC_COMM, KC_DOT, _______ \
),

/* Funct
 * ,---------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |KEYMAP|      |      |      |      |
 * | Tab  |M CUT |M COPY|MPASTE|M FIND|   URL|DMPLY1|DMREC1|  F11 |  F12 |
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |XXXXXX|      |      |      |      |      |      |
 * |      |      |      |XXXXXX|      |  DEL |DMPLY2|DMREC2|DMSTOP|ADMINI|
 * `---------------------------------------------------------------------'
 */
[_FUNCT] = KEYMAP( \
  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, \
  KC_TAB, MACCUT, MACCOPY, MACPASTE, MACFIND, M(SEND_KEYMAP_URI), DYN_MACRO_PLAY1, DYN_REC_START1, KC_F11,  KC_F12, \
  _______, _______, _______, _______, _______, KC_DEL, DYN_MACRO_PLAY2, DYN_REC_START2, DYN_REC_STOP, ADMINI \
),
[_RFUNCT] = RKEYMAP( \
  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, \
  KC_TAB, MACCUT, MACCOPY, MACPASTE, MACFIND, M(SEND_KEYMAP_URI), DYN_MACRO_PLAY1, DYN_REC_START1, KC_F11,  KC_F12, \
  _______, _______, _______, _______, _______, KC_DEL, DYN_MACRO_PLAY2, DYN_REC_START2, DYN_REC_STOP, RADMINI \
),

/* Arrow
 * ,---------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |SPOT  |
 * | Esc  | Tab  |  Up  |      |      |      |      |PREVWK|NEXTWK|LIGHT |
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |MISSIO|
 * |Adjust| Left | Down | Right|      | Left | Down |  Up  | Right|NCTRL |
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |      |XXXXXX|      |      |      |
 * |M UNDO| Alt  | GUI  |M REDO|      |      |XXXXXX|  Alt |  GUI |      |
 * `---------------------------------------------------------------------'
 */
[_ARROW] = KEYMAP( \
  KC_ESC, KC_TAB, KC_UP, _______, _______, _______, _______, PREVWKS, NEXTWKS, SPTLGHT, \
  ADJUST, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, MISSIONCTL, \
  MACUNDO, KC_LALT, KC_LGUI, MACREDO, _______, _______, _______, KC_LALT, KC_LGUI, _______ \
),
[_RARROW] = RKEYMAP( \
  KC_ESC, KC_TAB, KC_UP, _______, _______, _______, _______, PREVWKS, NEXTWKS, SPTLGHT, \
  RADJUST, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, MISSIONCTL, \
  MACUNDO, KC_LALT, KC_LGUI, MACREDO, _______, _______, _______, KC_LALT, KC_LGUI, _______ \
),

/* Adjust
 * ,---------------------------------------------------------------------.
 * |      |      |      |      |SCREEN|      |      |      |      |      |
 * |      | WhDn | MsUp | WhUp |  BRI+|      |      |      |      |Vol + |
 * |------+------+------+------+-------------+------+------+------+------|
 * |XXXXXX|      |      |      |SCREEN|      |      |      |      |      |
 * |XXXXXX|MsLeft|MsDown|MsRght|  BRI-|MsLeft|MsDown| MsUp |MsRght|Vol - |
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |      |XXXXXX|      |      |      |
 * |      |      |      | Lclk | Rclk |      |XXXXXX|      |      |Vol mt|
 * `---------------------------------------------------------------------'
 */
[_ADJUST] = KEYMAP( \
  _______, KC_WH_D, KC_MS_U, KC_WH_U, SCR_BR_UP, _______, _______, _______, _______, KC_VOLU, \
  _______, KC_MS_L, KC_MS_D, KC_MS_R, SCR_BR_DOWN, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_VOLD, \
  _______, _______, _______, KC_BTN1, KC_BTN2, _______, _______, _______, _______, KC_MUTE \
),
[_RADJUST] = RKEYMAP( \
  _______, KC_WH_D, KC_MS_U, KC_WH_U, SCR_BR_UP, _______, _______, _______, _______, KC_VOLU, \
  _______, KC_MS_L, KC_MS_D, KC_MS_R, SCR_BR_DOWN, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_VOLD, \
  _______, _______, _______, KC_BTN1, KC_BTN2, _______, _______, _______, _______, KC_MUTE \
),

/* Admini
 * ,---------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |Intell|L/R   |
 * | Reset|      |      |      |      |      |      |      |ijIDEA|SWITCH|
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |
 * |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |XXXXXX|      |      |      |      |      |XXXXXX|
 * |BL_TOG|BACKLI|      |XXXXXX|      |      |      |      |      |XXXXXX|
 * `---------------------------------------------------------------------'
 */
[_ADMINI] = KEYMAP( \
  RESET, _______, _______, _______, _______, _______, _______, _______, IJIDEA, RQWERTY, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  BL_TOGG, BACKLIT, _______, _______, _______, _______, _______, _______, _______, _______ \
),
[_RADMINI] = RKEYMAP( \
  RESET, _______, _______, _______, _______, _______, _______, _______, RIJIDEA, QWERTY, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  BL_TOGG, BACKLIT, _______, _______, _______, _______, _______, _______, _______, _______ \
),

/* for IntelliJ IDEA
 * ,---------------------------------------------------------------------.
 * |      |      |      |      |      |      |Cmd   |      |Cmd   |Cmd   |
 * | ESC  |PREVWK|NEXTWK|PREVTB|NEXTTB|      |Shft+R|Cmd+E |Shft+O|Shft+A|
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |      |Cmd   |Ctrl  | SLURP| SLURP|
 * |QWERTY|M COPY|MPASTE|SPTLGT|MSNCTL|      |Shft+F|Shft+E|  <-( | )->  |
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |      |Ctrl  |Ctrl  | BARF | BARF |
 * |DMSTOP|DMPLY1|DMPLY2|M UNDO|M REDO|      |Shft+N|Shft+M|  <-) | (->  |
 * `---------------------------------------------------------------------'
 */
[_IJIDEA] = KEYMAP( \
  KC_ESC, PREVWKS, NEXTWKS, PREVTAB, NEXTTAB, XXXXXXX, IDEA_R, ACTION_MODS_KEY(MOD_LGUI, KC_E), IDEA_O, IDEA_A, \
  QWERTY, MACCOPY, MACPASTE, SPTLGHT, MISSIONCTL, XXXXXXX, IDEA_F, IDEA_CURSV_EVAL, IDEA_SLURP_BACK, IDEA_SLURP_FORW, \
  DYN_REC_STOP, DYN_MACRO_PLAY1, DYN_MACRO_PLAY2, MACUNDO, MACREDO, XXXXXXX, IDEA_CURSV_CHNS, IDEA_CURSV_LOAD, IDEA_BARF_BACK, IDEA_BARF_FORW \
),
[_RIJIDEA] = RKEYMAP( \
  KC_ESC, PREVWKS, NEXTWKS, PREVTAB, NEXTTAB, XXXXXXX, IDEA_R, ACTION_MODS_KEY(MOD_LGUI, KC_E), IDEA_O, IDEA_A, \
  RQWERTY, MACCOPY, MACPASTE, SPTLGHT, MISSIONCTL, XXXXXXX, IDEA_F, IDEA_CURSV_EVAL, IDEA_SLURP_BACK, IDEA_SLURP_FORW, \
  DYN_REC_STOP, DYN_MACRO_PLAY1, DYN_MACRO_PLAY2, MACUNDO, MACREDO, XXXXXXX, IDEA_CURSV_CHNS, IDEA_CURSV_LOAD, IDEA_BARF_BACK, IDEA_BARF_FORW \
)

};

static uint16_t start;
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
        case SEND_KEYMAP_URI:
            if (record->event.pressed) {
                SEND_STRING("https://github.com/rinx/qmk_firmware_gherkin_rinx/blob/master/keymap.c");
            }
            break;
        case MAC_COPY_PASTE:
            if (record->event.pressed) {
                start = timer_read();
            } else {
                if (timer_elapsed(start) >= TAPPING_TERM)
                    return MACRO(D(LGUI), T(C), U(LGUI), END);
                else
                    return MACRO(D(LGUI), T(V), U(LGUI), END);
            }
            break;
        case WIN_COPY_PASTE:
            if (record->event.pressed) {
                start = timer_read();
            } else {
                if (timer_elapsed(start) >= TAPPING_TERM)
                    return MACRO(D(LCTL), T(C), U(LCTL), END);
                else
                    return MACRO(D(LCTL), T(V), U(LCTL), END);
            }
            break;
    }
    return MACRO_NONE;
};

void matrix_init_user(void) {
};

void matrix_scan_user(void) {
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_Q_ESC]  = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),
  [TD_W_TAB]  = ACTION_TAP_DANCE_DOUBLE(KC_W, KC_TAB),
  [TD_Q_TAB]  = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_TAB),
  [TD_P_SPL]  = ACTION_TAP_DANCE_DOUBLE(KC_P, SPTLGHT),
  [TD_X_ALT]  = ACTION_TAP_DANCE_DOUBLE(KC_X, KC_LALT),
  [TD_C_GUI]  = ACTION_TAP_DANCE_DOUBLE(KC_C, KC_LGUI)
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case RQWERTY:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_RQWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RLOWER:
      if (record->event.pressed) {
        layer_on(_RLOWER);
      } else {
        layer_off(_RLOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
    case RRAISE:
      if (record->event.pressed) {
        layer_on(_RRAISE);
      } else {
        layer_off(_RRAISE);
      }
      return false;
      break;
    case FUNCT:
      if (record->event.pressed) {
        layer_on(_FUNCT);
      } else {
        layer_off(_FUNCT);
      }
      return false;
      break;
    case RFUNCT:
      if (record->event.pressed) {
        layer_on(_RFUNCT);
      } else {
        layer_off(_RFUNCT);
      }
      return false;
      break;
    case ARROW:
      if (record->event.pressed) {
        layer_on(_ARROW);
      } else {
        layer_off(_ARROW);
      }
      return false;
      break;
    case RARROW:
      if (record->event.pressed) {
        layer_on(_RARROW);
      } else {
        layer_off(_RARROW);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case RADJUST:
      if (record->event.pressed) {
        layer_on(_RADJUST);
      } else {
        layer_off(_RADJUST);
      }
      return false;
      break;
    case ADMINI:
      if (record->event.pressed) {
        layer_on(_ADMINI);
      } else {
        layer_off(_ADMINI);
      }
      return false;
      break;
    case RADMINI:
      if (record->event.pressed) {
        layer_on(_RADMINI);
      } else {
        layer_off(_RADMINI);
      }
      return false;
      break;
    case IJIDEA:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_IJIDEA);
      }
      return false;
      break;
    case RIJIDEA:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_RIJIDEA);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      }
      return false;
      break;
    }
    return true;
};

