/* Copyright 2020 Bleleet <bleleet@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum atreus_layers {
    _COLEMAK,
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum atreus_keycodes {
    _LANG1 = SAFE_RANGE,
    _LANG2,
    _HEXPAD
};

#define LOWER LT(_LOWER,KC_SPC)
#define RAISE LT(_RAISE,KC_BSPC)
#define SPOT LCMD(KC_SPC)
#define TMUX LCTL(KC_B)
#define HOTK LALT(KC_SPC)
#define OSMCMD OSM(MOD_LGUI)
#define OSMCTL OSM(MOD_LCTL)
#define OSMALT OSM(MOD_LALT)
#define OSMSFT OSM(MOD_LSFT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT(
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_ESC,
    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                      KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    HOTK,    HOTK,    KC_K,    KC_H,    KC_COMM, KC_SCLN, KC_ENT,
    OSMCTL,  OSMALT,  SPOT,    KC_TAB,  LOWER,   OSMCMD,  OSMCMD,  RAISE,   OSMSFT,  TMUX,    OSMALT,  OSMCTL
  ),

  [_QWERTY] = LAYOUT(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_ESC,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    HOTK,    HOTK,    KC_N,    KC_M,    KC_COMM, KC_SCLN, KC_ENT,
    OSMCTL,  OSMALT,  SPOT,    KC_TAB,  LOWER,   OSMCMD,  OSMCMD,  RAISE,   OSMSFT,  TMUX,    OSMALT,  OSMCTL
  ),

  [_LOWER] = LAYOUT(
    KC_HOME, KC_PGUP, KC_PGDN, KC_END,  _LANG2,                    S(KC_E), KC_7,    KC_8,    KC_9,    S(KC_F),
    KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, _LANG1,                    S(KC_C), KC_4,    KC_5,    KC_6,    S(KC_D),
    KC_MRWD, KC_VOLU, KC_VOLD, KC_MFFD, KC_MPLY, _______, _______, S(KC_A), KC_1,    KC_2,    KC_3,    S(KC_B),
    _______, _______, _______, _______, _______, _______, _______, _______, KC_0,    _HEXPAD, KC_DOT,  _______
  ),

  [_RAISE] = LAYOUT(
	KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
	KC_QUOT, KC_AMPR, KC_ASTR, KC_SLSH, _______,                   _______, KC_PLUS, KC_MINS, KC_UNDS, KC_EQL,
	KC_DLR,  KC_EXLM, KC_LPRN, KC_RPRN, _______, _______, _______, _______, KC_LT,   KC_GT,   KC_DOT,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_ADJUST] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    KC_DQUO, KC_PIPE, KC_AT,   KC_BSLS, KC_F11,                    KC_F12,  KC_HASH, KC_PERC, KC_TILD, KC_GRV,
    KC_CIRC, KC_QUES, KC_LBRC, KC_RBRC, _______, _______, _______, _______, KC_LCBR, KC_RCBR, KC_COLN, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,  KC_DEL,  KC_CAPS
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint32_t default_layer;
    if (record->event.pressed) {
        switch (keycode) {
            case _LANG1:
                SEND_STRING(SS_LCTL(" "));
                //SEND_STRING(SS_TAP(X_ENT));
            case _LANG2:
                default_layer = biton32(default_layer_state);
                if (default_layer == _COLEMAK) {
                    set_single_persistent_default_layer(_QWERTY);
                }
                else if (default_layer == _QWERTY) {
                    set_single_persistent_default_layer(_COLEMAK);
                }
                break;
            case _HEXPAD:
                SEND_STRING("0x");
                break;
        }
    }
    return true;
}
