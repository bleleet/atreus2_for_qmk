/* Copyright 2020 Bleleet <bleleet@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
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
    _QUICK1,
    _QUICK2,
    _QUICK3,
    _QUICK4,
    _HEXPAD
};

#define LOWER LT(_LOWER,KC_SPC)
#define RAISE LT(_RAISE,KC_BSPC)
#define _SECH LCMD(KC_SPC)
#define _HOME LCMD(KC_H)
#define _TMUX LCTL(KC_B)
#define _MTRSFT RSFT_T(KC_ENT)
#define _MTLSFT LSFT_T(KC_Z)
#define _OSMCMD OSM(MOD_LGUI)
#define _OSMCTL OSM(MOD_LCTL)
#define _OSMALT OSM(MOD_LALT)
#define _OSMSFT OSM(MOD_LSFT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT(
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_ESC,
    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                      KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
    _MTLSFT, KC_X,    KC_C,    KC_D,    KC_V,    _HOME,   _SECH,   KC_K,    KC_H,    KC_COMM, KC_DOT,  _MTRSFT,
    _OSMCMD, _OSMCTL, _OSMALT,  KC_TAB, LOWER,   _OSMCTL, _OSMCMD, RAISE,   _TMUX,  _OSMALT, _OSMCTL, _OSMCMD
  ),

  [_QWERTY] = LAYOUT(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_ESC,
    _MTLSFT, KC_X,    KC_C,    KC_V,    KC_B,    _HOME,   _SECH,   KC_N,    KC_M,    KC_COMM, KC_DOT,  _MTRSFT,
    _OSMCMD, _OSMCTL, _OSMALT,  KC_TAB, LOWER,   _OSMCTL, _OSMCMD, RAISE,   _TMUX,  _OSMALT, _OSMCTL, _OSMCMD
  ),

 [_LOWER] = LAYOUT(
    KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_MPLY,                   KC_RBRC, KC_RCBR, KC_QUES, KC_EXLM, KC_COLN,
    KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, _LANG1,                    KC_RPRN, KC_UNDS, KC_MINS, KC_PLUS, KC_EQL,
    _QUICK1, _QUICK2, _QUICK3, _QUICK4, _LANG2,  _______, _______, KC_DQUO, KC_QUOT, KC_SCLN, KC_LT,   KC_GT,
    KC_MRWD, KC_VOLU, KC_VOLD, KC_MFFD, _______, _______, _______, _______, _______, _______, _______, _______
 ),

 [_RAISE] = LAYOUT(
    KC_GRV,  KC_AT,   KC_PERC, KC_LCBR, KC_LBRC,                   S(KC_E), KC_7,    KC_8,    KC_9,    S(KC_F),
    KC_DLR,  KC_HASH, KC_AMPR, KC_ASTR, KC_LPRN,                   S(KC_C), KC_4,    KC_5,    KC_6,    S(KC_D),
    KC_PIPE, KC_CIRC, KC_TILD, KC_SLSH, KC_BSLS, _______, _______, S(KC_A), KC_1,    KC_2,    KC_3,    S(KC_B),
    _______, _______, _______, _______, _______, _______, _______, _______, KC_0,    _HEXPAD, _______, _______
 ),

 [_ADJUST] = LAYOUT(
    _______, _______, _______, _______, _______,                   KC_F14,  KC_F7,   KC_F8,   KC_F9,   KC_F15,
    _______, _______, _______, _______, _______,                   KC_F12,  KC_F4,   KC_F5,   KC_F6,   KC_F13,
    _______, _______, _______, _______, _______, _______, _______, KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_F11,
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
                SEND_STRING(SS_TAP(X_ENT));
            case _LANG2:
                default_layer = biton32(default_layer_state);
                if (default_layer == _COLEMAK) {
                    set_single_persistent_default_layer(_QWERTY);
                }
                else if (default_layer == _QWERTY) {
                    set_single_persistent_default_layer(_COLEMAK);
                }
                break;
            case _QUICK1:
                SEND_STRING("''");
                SEND_STRING(SS_TAP(X_LEFT));
                break;
            case _QUICK2:
                SEND_STRING("[]");
                SEND_STRING(SS_TAP(X_LEFT));
                break;
            case _QUICK3:
                SEND_STRING("()");
                SEND_STRING(SS_TAP(X_LEFT));
                break;
            case _QUICK4:
                SEND_STRING("\"\"");
                SEND_STRING(SS_TAP(X_LEFT));
                break;
            case _HEXPAD:
                SEND_STRING("0x");
                break;
        }
    }
    return true;
}
