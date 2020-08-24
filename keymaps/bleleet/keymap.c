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
    LANG1 = SAFE_RANGE,
    LANG2,
    HEXPAD
};

#define LOWER LT(_LOWER,KC_SPC)
#define RAISE LT(_RAISE,KC_BSPC)
#define _SECH LCMD(KC_SPC)
#define _HOME LCMD(KC_H)
#define _VIM  KC_BSLS
#define _TMUX LCTL(KC_B)
#define MTLCTL LCTL_T(KC_Q)
#define MTRCTL RCTL_T(KC_ESC)
#define MTLSTF LSFT_T(KC_Z)
#define MTRSTF RSFT_T(KC_ENT)
#define OSMCMD OSM(MOD_LGUI)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT(
    MTLCTL,  KC_W,    KC_F,    KC_P,    KC_B,                      KC_J,    KC_L,    KC_U,    KC_Y,    MTRCTL,
    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                      KC_K,    KC_N,    KC_E,    KC_I,    KC_O,
    MTLSTF,  KC_X,    KC_C,    KC_D,    KC_V,    _HOME,   _SECH,   KC_M,    KC_H,    KC_COMM, KC_DOT,  MTRSTF,
    KC_LCMD, KC_LCTL, KC_LALT, _VIM,    LOWER,   _TMUX,   OSMCMD,  RAISE,   KC_TAB,  KC_RALT, KC_RCTL, KC_RCMD
  ),

  [_QWERTY] = LAYOUT(
    MTLCTL,  KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    MTRCTL,
    MTLSTF,  KC_X,    KC_C,    KC_V,    KC_B,    _HOME,   _SECH,   KC_N,    KC_M,    KC_COMM, KC_DOT,  MTRSTF,
    KC_LCMD, KC_LCTL, KC_LALT, _VIM,    LOWER,   _TMUX,   OSMCMD,  RAISE,   KC_TAB,  KC_RALT, KC_RCTL, KC_RCMD
  ),

 [_LOWER] = LAYOUT(
    KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_MPLY,                   S(KC_E), KC_7,    KC_8,    KC_9,    S(KC_F),
    KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, LANG2,                     S(KC_C), KC_4,    KC_5,    KC_6,    S(KC_D), 
    KC_MRWD, KC_VOLU, KC_VOLD, KC_MFFD, LANG1,   _______, _______, S(KC_A), KC_1,    KC_2,    KC_3,    S(KC_B),
    _______, _______, _______, _______, _______, _______, HEXPAD,  _______, KC_0,    _______, _______, _______
 ),

 [_RAISE] = LAYOUT(
    KC_GRV,  KC_QUOT, KC_DQUO, KC_HASH, KC_PIPE,                   KC_BSLS, KC_SLSH, KC_QUES, KC_EXLM, KC_DLR,
    KC_LCBR, KC_RCBR, KC_AMPR, KC_ASTR, KC_PERC,                   KC_AT,   KC_UNDS, KC_MINS, KC_PLUS, KC_EQL,
    KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_CIRC, _______, _______, KC_TILD, KC_LT,   KC_GT,   KC_SCLN, KC_COLN,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
 ),

 [_ADJUST] = LAYOUT(
    _______, _______, _______, _______, _______,                   KC_F14,  KC_F7,   KC_F8,   KC_F9,   KC_F15,
    _______, _______, _______, _______, _______,                   KC_F12,  KC_F4,   KC_F5,   KC_F6,   KC_F13,
    KC_CAPS, KC_DEL,  KC_INS,  _______, _______, _______, _______, KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_F11,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
 )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint32_t default_layer;
    if (record->event.pressed) {
        switch (keycode) {
            case LANG1:
                SEND_STRING(SS_LCTL(" ") SS_TAP(X_ENT));
            case LANG2:
                default_layer = biton32(default_layer_state);
                if (default_layer == _COLEMAK) {
                    set_single_persistent_default_layer(_QWERTY);
                }
                else if (default_layer == _QWERTY) {
                    set_single_persistent_default_layer(_COLEMAK);
                }
                break;
            case HEXPAD:
                SEND_STRING("0x");
                break;
        }
    }
    return true;
}
